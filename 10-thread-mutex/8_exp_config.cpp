#include <unordered_map>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

using TParams = std::vector<std::pair<int, int>>;

thread_local std::unordered_map<int, int> experiments = {{42, 42}};
std::mutex m;

void process() {
    std::scoped_lock(m);

    for (const auto& [k, v] : experiments) {
        std::cout << k << ": " << v << std::endl;
    }
    std::cout << std::endl;
}

void process_request(const TParams& params) {
    for (const auto& [k, v] : params) {
        experiments[k] = v;
    }

    process();
}

int main() {
    std::thread t([&] {
        process_request(TParams{{1, 2}});
    });

    std::thread t2([&] {
        process_request(TParams{{10, 20}});
    });

    t.join();
    t2.join();
}
