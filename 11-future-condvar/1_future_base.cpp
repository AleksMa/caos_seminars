#include <future>
#include <thread>
#include <iostream>

int main() {
    std::promise<int> pr;
    std::future<int> fut = pr.get_future();

    std::thread t([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(100));
        try {
            pr.set_value(42);
            // throw std::runtime_error("some error");
        } catch(...) {
            pr.set_exception(std::current_exception());
        }
    });

    std::cout << "Waiting..." << std::endl;

    // try {
    //     int x = fut.get();
    //     std::cout << "Result = " << x << std::endl;
    // } catch (std::exception& e) {
    //     std::cout << e.what() << std::endl;
    // }

    const auto status = fut.wait_for(std::chrono::duration(std::chrono::seconds(1)));
    if (status == std::future_status::timeout) {
        std::cout << "Timeout" << std::endl;
        t.detach();
        return 42;
    }

    std::cout << "Waited" << std::endl;

    int x = fut.get();
    std::cout << "Result = " << x << std::endl;

    t.join();
}
