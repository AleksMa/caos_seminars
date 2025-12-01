#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <chrono>

int main() {
    std::thread t([&] {
        std::cout << "Hello from thread#1" << std::endl;
        exit(42);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    });

    std::thread t2([&] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Hello from thread#2" << std::endl;
    });

     t.join();
    t2.join();

    std::cout << "Finish" << std::endl;
}
