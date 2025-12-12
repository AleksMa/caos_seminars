#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <thread>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) { // FD + PORT
        std::perror("bind");
        close(server_fd);
        return 1;
    }

    int queue_size = 16;
    listen(server_fd, queue_size);
    std::cout << "Server is listening on http://localhost:8080\n";

    const char* response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html><body><h1>Hello, world!</h1></body></html>";

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd == -1) {
            std::perror("accept");
            continue;
        }

        std::thread([&] {
            char buf[1024];
            ssize_t n = recv(client_fd, buf, sizeof(buf), 0);  // freeze

            if (n > 0) {
                std::cout << "Got request (" << n << " bytes)\n";

                std::cout.write(buf, n);
                std::cout << "\n---\n";
            }

            send(client_fd, response, std::strlen(response), 0);
            close(client_fd);
        }).detach();
    }

    close(server_fd);
    return 0;
}
