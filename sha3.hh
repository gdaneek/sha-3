#ifndef __SHA_HH
#define __SHA_HH

#include <utility>
#include <cstdint>
#include <cstdlib>

constexpr uint64_t rc[] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808A,
    0x8000000080008000, 0x000000000000808B, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008A,
    0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089,
    0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800A, 0x800000008000000A, 0x8000000080008081,
    0x8000000000008080, 0x0000000080000001, 0x8000000080008008,
};

constexpr uint8_t r_arr[] = {0,  1, 62, 28, 27, 36, 44, 6,  55,
                             20, 3, 10, 43, 25, 39, 41, 45, 15,
                             21, 8, 18, 2,  61, 56, 14};

constexpr uint8_t pi_index[] = {
    0, 6, 12, 18, 24,
    3, 9, 10, 16, 22,
    1, 7, 13, 19, 20,
    4, 5, 11, 17, 23,
    2, 8, 14, 15, 21};


using ui64 = uint64_t;
template<int n > using make_is = std::make_index_sequence<n>;
template<size_t... i> using is = std::index_sequence<i...>;

void sha3_224(const uint8_t* data, uint8_t* out, const uint64_t fsize);
void sha3_256(const uint8_t* data, uint8_t* out, const uint64_t fsize);
void sha3_384(const uint8_t* data, uint8_t* out, const uint64_t fsize);
void sha3_512(const uint8_t* data, uint8_t* out, const uint64_t fsize);

#endif // __SHA_HH
