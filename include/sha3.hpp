/**
 * @file    sha3.hpp
 * @brief   Implementation of SHA-3 hash algo (all modes - 224, 384, 256 and 512)
 * @author  https://github.com/gdaneek
 * @see https://github.com/gdaneek/sha-3
 */
#ifndef SHA_3_IMPL_HPP
#define SHA_3_IMPL_HPP

#include <utility>
#include <cstring>
#include "constant.hh"

#define UNROLL(A, F) [&]<uint64_t... i>(std::index_sequence<i...>) __attribute__((always_inline)) { ((A), ...); }(std::make_index_sequence<(F)>());

template<std::size_t bsz>
inline auto core(const void * __restrict in, uint64_t * __restrict s) {
    uint64_t c[5], t[25];
    UNROLL(s[i] ^= ((const uint64_t* __restrict)in)[i], bsz >> 3);

    for(uint64_t rnd{};rnd < nr;rnd++) {
        UNROLL(c[i] = s[i] ^ s[i + 5] ^ s[i + 10] ^ s[i + 15] ^ s[i + 20], 5);
        UNROLL(s[i] ^= (c[(i + 1) % 5] << 1 | c[(i + 1) % 5] >> 63) ^ c[(i + 4) % 5], 25);
        UNROLL(t[i] = s[pi[i]] << rot[pi[i]] | s[pi[i]] >> (64 - rot[pi[i]]), 25);
        UNROLL(s[i] = (~t[i / 5 * 5 + (i + 1) % 5] & t[i / 5 * 5 + (i + 2) % 5]) ^ t[i], 25);
        *s ^= rc[rnd];
    }
}

/**
 * @brief SHA-3 implementation (main func)
 * @tparam mode SHA-3 hash mode (224, 256, 384 or 512 bit)
 * @param in input bytes
 * @param out output bytes (hash)
 * @param sz num of input bytes
 */
template<uint64_t mode>
inline void sha3(void* out, const void* in, const uint64_t sz) {
    constexpr uint16_t bsz = (b - (mode << 1)) >> 3;
    uint64_t s[b >> 6] = {0}, n = sz / bsz, resid = sz % bsz;
    uint8_t bbuf[bsz] = {0};
    bbuf[bsz - 1] = 0x80;
    bbuf[resid] |= 0x06;

    for (uint64_t i{};i < n;i++) core<bsz>(&((char*)in)[i * bsz], s);
    memcpy(bbuf, &((char*)in)[sz - resid], resid);
    core<bsz>(bbuf, s);
    UNROLL(((char*)out)[i] = ((char*)s)[i], mode >> 3);
}

#endif // SHA_3_IMPL_HPP
