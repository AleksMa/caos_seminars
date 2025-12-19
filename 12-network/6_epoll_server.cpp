#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 128);

    int epfd = epoll_create1(0);

    epoll_event ev{};
    ev.events = EPOLLIN;
    ev.data.fd = server_fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &ev);

    const char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html><body><h1>Hello from epoll</h1></body></html>";

    epoll_event events[64];
    while (true) {
        int n = epoll_wait(epfd, events, 64, -1);

        for (int i = 0; i < n; ++i) {
            int fd = events[i].data.fd;

            if (fd == server_fd) {
                int client_fd = accept(server_fd, nullptr, nullptr);

                epoll_event client_ev{};
                client_ev.events = EPOLLIN;
                client_ev.data.fd = client_fd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &client_ev);
            } else {
                char buf[1024];
                ssize_t count = recv(fd, buf, sizeof(buf), 0);

                if (count > 0) {
                    std::cout << "Got request (" << count << " bytes)\n";

                    std::cout.write(buf, count);
                    std::cout << "\n---\n";

                    send(fd, response, sizeof(response) - 1, 0);
                } 

                close(fd);
                epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr);
            }
        }
    }

    close(epfd);
    close(server_fd);
    return 0;
}
