#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <array>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " NODE SERVICE\n";
        return 1;
    }

    const std::string node    = argv[1];
    const std::string service = argv[2];

    addrinfo hints{};
    hints.ai_family = AF_INET6;

    addrinfo* raw = nullptr;
    int gai_err = getaddrinfo(node.c_str(), service.data(), &hints, &raw);
    if (gai_err != 0) {
        std::cerr << "gai error: " << gai_strerror(gai_err) << std::endl;
        return 2;
    }

    std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> res(raw, freeaddrinfo); // freeaddrinfo(raw)
    for (addrinfo* ai = res.get(); ai; ai = ai->ai_next) {
        std::cout << "ai_flags=" << ai->ai_flags
                  << ", ai_family=" << ai->ai_family
                  << ", ai_socktype=" << ai->ai_socktype
                  << "\n";

        std::array<char, 1024> buf{};

        switch (ai->ai_family) {
            case AF_INET: {
                auto* inet = reinterpret_cast<sockaddr_in*>(ai->ai_addr);
                const char* addr = inet_ntop(AF_INET, &inet->sin_addr,  // net to presentation
                                             buf.data(), buf.size());
                if (!addr) addr = "<inet_ntop failed>";
                std::cout << "\taddress: " << addr
                          << ", port: " << ntohs(inet->sin_port) << "\n";  // net to host short
                break;
            }

            case AF_INET6: {
                auto* inet6 = reinterpret_cast<sockaddr_in6*>(ai->ai_addr);
                const char* addr = inet_ntop(AF_INET6, &inet6->sin6_addr,
                                             buf.data(), buf.size());
                if (!addr) addr = "<inet_ntop failed>";
                std::cout << "\taddress: " << addr
                          << ", port: " << ntohs(inet6->sin6_port) << "\n";
                break;
            }

            default:
                std::cout << "\tunknown address family\n";
                break;
        }
    }

    return 0;
}

// ./a.out ya.ru http
