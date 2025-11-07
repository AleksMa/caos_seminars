#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main() {
    int fd = open("data.bin", O_RDWR | O_CREAT, 0666);
    ftruncate(fd, 4096);

    void* p = mmap(nullptr, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy((char*)p, "test");

    ftruncate(fd, 8192);
    p = mremap(p, 4096, 8192, MREMAP_MAYMOVE);
    strcpy((char*)p + 4096, "more data");

    msync(p, 8192, MS_SYNC);
    munmap(p, 8192);
    close(fd);
}
