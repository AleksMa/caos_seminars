#include <future>
#include <thread>
#include <iostream>

std::future<std::string> runAsync() {
    std::promise<std::string> pr;
    std::future<std::string> fut = pr.get_future();

    std::thread([p = std::move(pr)]() mutable {  // MOVE only!
        std::cout << "Starting request..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Acquired request" << std::endl;

        p.set_value("Response");
    }).detach();

    return fut;
}

int main() {
    auto f = runAsync();

    std::cout << "Some main work..." << std::endl;

    const auto result = f.get();
    std::cout << "Future result: " << result << std::endl;
}
