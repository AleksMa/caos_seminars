/*
 * Открыть файл и записать его в виртуальную память.
 * Заменить каждый символ на '*' в этом файле
 * файл для теста - small_file.txt
 */

#include <iostream>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

int main(int argc, char* argv[]) {
    int fd = open("bank.txt", O_RDWR);
    if (fd == -1) {
        std::cerr << "open: " << std::strerror(errno) << std::endl;
        exit(1);
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        std::cerr << "fstat: " << std::strerror(errno) << std::endl;
        exit(1);
    }

    int input_size = st.st_size;
    void* mp = mmap(nullptr, input_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mp == MAP_FAILED) {
        std::cerr << "mmap: " << std::strerror(errno) << std::endl;
        exit(1);
    }


    char* data = static_cast<char*>(mp);

    for (int i = 0; i < input_size; ++i) {
        if (std::isdigit(data[i])) {
            data[i] = '*';
        }
        std::cout << data[i] << std::endl;
    }

    getchar();

    if (close(fd) == -1) {
        std::cerr << "close: " << std::strerror(errno) << std::endl;
        exit(1);
    }

    if (munmap(mp, input_size) == -1) {
        std::cerr << "munmap: " << std::strerror(errno) << std::endl;
        exit(1);
    }

    return 0;
}
