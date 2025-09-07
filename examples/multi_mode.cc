/**
 * @file    multi_mode.cc
 * @brief   Example of usage SHA-3 implementation from sha3.hpp with mmap file processing
 * @author  https://github.com/gdaneek
 * @see https://github.com/gdaneek/sha-3
 */
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>

#include "sha3.hpp"

int main(int argc, char* argv[]) {
  int fd = open(argv[2], O_RDONLY);
  uint16_t mode = atoi(argv[1]);

  if (fd == -1)
    return 1;

  uint64_t file_size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);

  void* mapped = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE /* | MAP_POPULATE */, fd, 0);

  if (mapped == MAP_FAILED) {
    close(fd);
    return 1;
  }

  alignas(32) uint8_t out[512 >> 3];

  switch (mode) {
    case 512: {
      sha3<512>(out, mapped, file_size);
      UNROLL(printf("%02x", out[I]), 512 >> 3);
      break;
    }

    case 256: {
      sha3<256>(out, mapped, file_size);
      UNROLL(printf("%02x", out[I]), 256 >> 3);
      break;
    };

    case 384: {
      sha3<384>(out, mapped, file_size);
      UNROLL(printf("%02x", out[I]), 384 >> 3);
      break;
    }

    case 224: {
      sha3<224>(out, mapped, file_size);
      UNROLL(printf("%02x", out[I]), 224 >> 3);
      break;
    }
  };

  printf("\n");

  munmap(mapped, file_size);
  close(fd);
  return 0;
}
