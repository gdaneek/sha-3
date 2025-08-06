/**
 * @file    sha3.hpp
 * @brief   Implementation of SHA-3 hash algo (all modes - 224, 384, 256 and 512)
 * @author  https://github.com/gdaneek
 * @see https://github.com/gdaneek/sha-3
 */
#ifndef SHA_3_IMPL_HPP
#define SHA_3_IMPL_HPP

#include <cstring>
#include <utility>
#include "constant.hh"

#define UNROLL(A, F) [&]<uint64_t... I>(std::index_sequence<I...>) \
                     __attribute__((always_inline)) { ((A), ...); } (std::make_index_sequence<(F)>());

template<std::size_t m_mode>
class SHA3 {
  alignas(32) uint64_t s[b >> 6] = {0};
public:

  static constexpr auto block_size() {
    return (b - (m_mode << 1)) >> 3;
  }

  void update(const void* __restrict in, const uint64_t sz) {
    alignas(32) uint64_t c[5], t[25];
    for (uint64_t i{}; i < sz; i += block_size()) {
      UNROLL(s[I] ^= ((const uint64_t* __restrict)&((char*)in)[i])[I], block_size() >> 3);
      for (uint64_t rnd{}; rnd < nr; rnd++) {
        UNROLL(c[I] = s[I] ^ s[I + 5] ^ s[I + 10] ^ s[I + 15] ^ s[I + 20], 5);
        UNROLL(s[I] ^= (c[(I + 1) % 5] << 1 | c[(I + 1) % 5] >> 63) ^ c[(I + 4) % 5], 25);
        UNROLL(t[I] = s[pi[I]] << rot[pi[I]] | s[pi[I]] >> (64 - rot[pi[I]]), 25);
        UNROLL(s[I] = (~t[I / 5 * 5 + (I + 1) % 5] & t[I / 5 * 5 + (I + 2) % 5]) ^ t[I], 25);
        s[0] ^= rc[rnd];
      }
    }
  }

  void finalize(void* __restrict out, const void* __restrict in, const uint64_t sz) {
    uint64_t resid = sz % block_size();
    update(in, sz - resid);

    alignas(32) uint8_t buff[block_size()] = {0};
    buff[block_size() - 1] = 0x80;
    buff[resid] |= 0x06;
    memcpy(buff, &((char*)in)[sz - resid], resid);
    update(buff, block_size());
    memcpy(out, s, m_mode >> 3);
  }

  auto operator()(auto&&... v) {
    return finalize(std::forward<decltype(v)>(v)...);
  }
};

template<std::size_t m_mode>
void sha3(auto&&... v) { SHA3<m_mode>{}(std::forward<decltype(v)>(v)...); }

#endif  // SHA_3_IMPL_HPP
