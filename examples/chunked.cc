/**
 * @file    chunked.cc
 * @brief   Example of usage SHA-3 implementation from sha3.hpp with chunked file processing
 * @author  https://github.com/gdaneek
 * @see https://github.com/gdaneek/sha-3
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cinttypes>

#include "sha3.hpp"

int main(int argc, char** argv) {
  #ifdef SHA_3_512
  SHA3<512> sha3;
  #elif defined(SHA_3_256)
  SHA3<256> sha3;
  #elif defined(SHA_3_384)
  SHA3<384> sha3;
  #elif defined(SHA_3_224)
  SHA3<224> sha3;
  #endif

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) return 1;

  uint64_t file_size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);

  constexpr auto ALIGMENT = 64;

  constexpr auto lcm = [](int a, int b) {
    auto gcd = a, _b = b;
    while (_b) {
		gcd %= _b;
		std::swap (gcd, _b);
	}
	return a / gcd * b;
  } (sha3.block_size(), ALIGMENT);

  constexpr auto CHUNK_SIZE = (1 << 25) - ((1 << 25) % lcm); // 32MB for example; OK for very large files

  char* buf;
  if (posix_memalign((void**)&buf, ALIGMENT, CHUNK_SIZE)) {
    perror("posix_memalign");
    close(fd);
    return 1;
  }

  size_t bytes_read, tot{};
  alignas(32) uint8_t out[512 >> 3]{};

  while ((bytes_read = read(fd, buf, CHUNK_SIZE)) > 0) {
    tot += bytes_read;
    if (tot != file_size) [[likely]] {
      sha3.update(buf, bytes_read);
    } else {
      sha3.finalize(out, buf, bytes_read);
    }
  }

  #ifdef SHA_3_512
  UNROLL(printf("%02x", out[I]), 512 >> 3);
  #elif defined(SHA_3_256)
  UNROLL(printf("%02x", out[I]), 256 >> 3);
  #elif defined(SHA_3_384)
  UNROLL(printf("%02x", out[I]), 384 >> 3);
  #elif defined(SHA_3_224)
  UNROLL(printf("%02x", out[I]), 224 >> 3);
  #endif

  printf("\n");

  free(buf);
  close(fd);

  return 0;
}
