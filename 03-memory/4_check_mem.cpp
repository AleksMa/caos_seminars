
#include <iostream>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <cstdint>


constexpr uint64_t DATA_SIZE = 5ULL * 1024 * 1024 * 1024;

int main() {
    const char* filename = "data.bin";

    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    ftruncate(fd, DATA_SIZE);

    void* mp =  mmap(nullptr, DATA_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);

    char* data = static_cast<char*>(mp);

    for (uint64_t i = 0; i < DATA_SIZE; ++i) {
        data[i] = '*';
    }

    munmap(mp, DATA_SIZE);

    return 0;
}
