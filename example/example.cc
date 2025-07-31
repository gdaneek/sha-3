#include <sys/mman.h> // mmap, munmap
#include <fcntl.h>    // open
#include <unistd.h>   // close
#include <cstdio>

#include "sha3.hh"

int main(int argc, char* argv[]) {

    uint16_t hash_sz = atoi(argv[1]);
    char* path = argv[2];

    int fd = open(argv[2], O_RDONLY);
    if (fd == -1) return 1;

    ui64 file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    void* mapped = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        close(fd);
        return 1;
    }

    uint8_t out[512 >> 3];
    auto in = reinterpret_cast<const uint8_t*>(mapped);

    if(hash_sz == 512)      [[likely]] sha3_512(in, out, file_size);
    else if(hash_sz == 256) [[likely]]  sha3_256(in, out, file_size);
    else if(hash_sz == 384) [[unlikely]] sha3_384(in, out, file_size);
    else if(hash_sz == 224) [[unlikely]] sha3_224(in, out, file_size);

    auto print{[]<ui64... i>(uint8_t *arr, is<i...>) { (printf("%02x", arr[i]), ...); }};

    if(hash_sz == 512)      [[likely]]   print(out, make_is<(512 >> 3)>());
    else if(hash_sz == 256) [[likely]]   print(out, make_is<(256 >> 3)>());
    else if(hash_sz == 384) [[unlikely]] print(out, make_is<(384 >> 3)>());
    else if(hash_sz == 224) [[unlikely]] print(out, make_is<(224 >> 3)>());

    printf("\n");

    munmap(mapped, file_size);
    close(fd);
    return 0;
}
