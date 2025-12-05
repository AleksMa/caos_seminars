#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <iostream>

// O_APPEND - дописывать в конец файла
// O_CREAT - создать файл, если его не существует
// O_TRUNK - очистить файл, если он уже существует
// O_RDONLY - открыть файл для чтения
// O_WRONLY - открыть файл для записи
// O_RDWR - открыть файл для чтения и записи
//
// если указан O_CREATE, то нужно также указать
// права, с которыми будет создан файл

int main(int argc, char **argv) {
    umask(0022);

    const char *src =  "input.txt";
    getchar();
    int in_fd = open(src, O_RDONLY);
    getchar();
    if (in_fd == -1) {
        std::cerr << errno << " " << std::strerror(errno) << std::endl;
        return 1;
    }

    close(in_fd);
    getchar();

    return 0;
}
