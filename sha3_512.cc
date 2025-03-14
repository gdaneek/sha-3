#include <sys/mman.h> // mmap, munmap
#include <fcntl.h>    // open
#include <unistd.h>   // close
#include <cstdio>

#include "sha3.hh"

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) return 1;

    ui64 file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    void* mapped = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        close(fd);
        return 1;
    }

    uint8_t out[512 >> 3];
    sha3_512(reinterpret_cast<const uint8_t*>(mapped), out, file_size);
    []<ui64... i>(uint8_t *arr, is<i...>) { (printf("%02x", arr[i]), ...); }(out, make_is<(512 >> 3)>());
    printf("\n");
    munmap(mapped, file_size);
    close(fd);
    return 0;
}

