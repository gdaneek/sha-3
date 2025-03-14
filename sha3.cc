#include "sha3.hh"

template<int dval>
void sha3(const uint8_t* data, uint8_t* out, const uint64_t fsize) {
    constexpr uint16_t block_sz = (1600 - (dval << 1)) >> 3, b = 1600, nr = 24;
    ui64 s[b >> 6] = {0}, s2[b >> 6], c[5], d[5], szdiff = 0;
    ui64 real_length = (fsize + block_sz) / block_sz * block_sz;
    uint8_t bbuf[block_sz] = {0};
    const uint8_t* pin = data;

    for (uint64_t offset = 0; offset < real_length;offset += block_sz, pin += block_sz) {
        if(offset+block_sz > fsize) {
            szdiff = fsize - offset, pin = bbuf, bbuf[szdiff] = 0x06, bbuf[block_sz-1] = 0x80;
            for(int i = 0;i < szdiff;i++) bbuf[i] = data[i+offset];
        }
        [&s]<ui64 ... i>(auto pin, is<i...>) {((s[i] ^= pin[i]), ...);}(reinterpret_cast<const ui64*>(pin), make_is<(block_sz >> 3)>());
        for(int rnd = 0;rnd < nr;rnd++) {
            [&s, &c]<ui64... i>(is<i...>) { ((c[i] = s[i] ^ s[i+5] ^ s[i+10] ^ s[i+15] ^ s[i+20]), ...); } (make_is<5>());
            [&c, &d]<ui64... i>(is<i...>) { ((d[i] = c[(i+4)%5] ^ ((c[(i+1)%5] << 1) | (c[(i+1)%5] >> 63))), ...);} (make_is<5>());
            [&s, &d]<ui64... i>(is<i...>) { ((s[i] ^= d[i % 5]), ...); }(make_is<25>());
            [&s]<ui64... i>(is<i...>) { ((s[i + 1] = (s[i + 1] << r_arr[i+1]) | (s[i + 1] >> (64-r_arr[i+1]))), ...); } (make_is<24>());
            [&s, &s2]<ui64... i>(is<i...>) { ((s2[i] = s[pi_index[i]]), ...); } (make_is<25>());
            [&s, &s2]<ui64... i>(is<i...>) { ((s[i] = s2[i] ^ ((~s2[(i/5)*5+(i+1)%5]) & s2[(i/5)*5 + (i+2)%5])), ...); } (make_is<25>());
            *s ^= rc[rnd];
        }
    }
    []<ui64... i>(uint8_t* out, ui64* s, is<i...>) { ((out[i] = (uint8_t)(s[i>>3]>>((i%8)<<3))), ...); } (out, s, make_is<(dval>>3)>());
}

void sha3_224(const uint8_t* data, uint8_t* out, const uint64_t fsize) { sha3<224>(data, out, fsize); }
void sha3_256(const uint8_t* data, uint8_t* out, const uint64_t fsize) { sha3<256>(data, out, fsize); }
void sha3_384(const uint8_t* data, uint8_t* out, const uint64_t fsize) { sha3<384>(data, out, fsize); }
void sha3_512(const uint8_t* data, uint8_t* out, const uint64_t fsize) { sha3<512>(data, out, fsize); }
