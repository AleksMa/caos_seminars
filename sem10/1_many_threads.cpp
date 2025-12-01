#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <system_error>

void worker()
{
    // std::this_thread::sleep_for(std::chrono::hours(1));
}

// uint32_t p;
// 2^32 bytes = 4 Gb;

int main()
{
    std::vector<std::thread> threads;
    threads.reserve(100000);

    try {
        for (size_t i = 0; ; ++i) {
            threads.emplace_back(worker);
        }
    } catch (const std::system_error& e) {
        std::cerr << "code=" << e.code() << "\n";
        std::cerr << "Всего потоков: " << threads.size() << std::endl;
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.detach();
        }
    }

    return 0;
}
