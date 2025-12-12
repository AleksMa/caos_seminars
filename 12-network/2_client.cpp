#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <host> <port>\n";
        return 1;
    }

    const char* host = argv[1];
    const char* port = argv[2];

    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo* res;
    int err = getaddrinfo(host, port, &hints, &res);
    if (err != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(err) << "\n";
        return 1;
    }

    int sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    connect(sock_fd, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);

    std::string req =
        "GET / HTTP/1.1\r\n"
        "Host: " + std::string(host) + "\r\n"
        "Connection: close\r\n"
        "\r\n";

    send(sock_fd, req.data(), req.size(), 0);

    char buf[4096];
    while (true) {
        ssize_t n = recv(sock_fd, buf, sizeof(buf), 0);
        if (n <= 0) {
            break;
        }

        std::cout.write(buf, n);
    }

    close(sock_fd);
    return 0;
}
