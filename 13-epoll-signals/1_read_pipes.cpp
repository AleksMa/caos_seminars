#include <iostream>
#include <cstdlib>

#include <unistd.h>
#include <fcntl.h>

constexpr std::size_t BUFFER_SIZE = 1024;

void make_read_non_block(int fd) {
    int flags = ::fcntl(fd, F_GETFL, 0);
    ::fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2>\n";
        std::exit(1);
    }

    int fd1 = ::open(argv[1], O_RDONLY | O_NONBLOCK);
    int fd2 = ::open(argv[2], O_RDONLY | O_NONBLOCK);

    // make_read_non_block(fd1);
    // make_read_non_block(fd2);

    char buf[BUFFER_SIZE];

    while (true) {
        ssize_t size1 = ::read(fd1, buf, BUFFER_SIZE);
        if (size1 > 0) {
            std::cout << "[CH1]: "
                      << std::string_view(buf, static_cast<std::size_t>(size1));
        }
        std::cout << "size1=" << size1 << std::endl;

        ssize_t size2 = ::read(fd2, buf, BUFFER_SIZE);
        if (size2 > 0) {
            std::cout << "[CH2]: "
                      << std::string_view(buf, static_cast<std::size_t>(size2));
        }
        std::cout << "size2=" << size1 << std::endl;

        if (!size1 && !size2) {
            break;
        }
    }

    ::close(fd1);
    ::close(fd2);

    return 0;
}
