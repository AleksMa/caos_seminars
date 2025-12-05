#include <iostream>
#include <thread>
#include <future>

int func(int i) {
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 123 + i;
}

int main() {
    std::future<int> f = std::async(func, 1);
    // std::future<int> f = std::async(std::launch::deferred, func, 1);

    std::cout << "Some work..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Finished work – wait for future" << std::endl;

    std::cout << f.get() << std::endl;
}