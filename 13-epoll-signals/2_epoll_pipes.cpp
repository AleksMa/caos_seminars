#include <iostream>
#include <cstdlib>
#include <string_view>
#include <array>

#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

constexpr std::size_t BUFFER_SIZE = 1024;
constexpr int MAX_EVENTS = 2;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2>\n";
        std::exit(1);
    }

    int fd1 = ::open(argv[1], O_RDONLY);
    int fd2 = ::open(argv[2], O_RDONLY);

    char buf[BUFFER_SIZE];

    int epoll_fd = ::epoll_create1(0);

    epoll_event event{};
    event.events = EPOLLIN | EPOLLHUP;

    event.data.fd = fd1;
    ::epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd1, &event);

    event.data.fd = fd2;
    ::epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd2, &event);

    int open_channels = 2;

    while (open_channels) {
        std::array<epoll_event, MAX_EVENTS> events{};
        int num_events = ::epoll_wait(
            epoll_fd,
            events.data(),
            static_cast<int>(events.size()),
            -1
        );

        for (int i = 0; i < num_events; ++i) {
            int fd = events[i].data.fd;

            if (events[i].events & EPOLLHUP) {
                std::cout << "channel closed\n";
            }

            ssize_t size = ::read(fd, buf, BUFFER_SIZE);
            if (size > 0) {
                if (fd == fd1) {
                    std::cout << "[CH1]: "
                              << std::string_view(buf, static_cast<std::size_t>(size));
                } else if (fd == fd2) {
                    std::cout << "[CH2]: "
                              << std::string_view(buf, static_cast<std::size_t>(size));
                }
            } else if (size == 0) {
                ::close(fd);
                --open_channels;
            }
        }
    }

    ::close(epoll_fd);
    return 0;
}
