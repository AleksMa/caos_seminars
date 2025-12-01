#include <iostream>
#include <thread>
#include <chrono>

void heavy_task(std::stop_token st) {
    std::stop_callback cb(st, []{
        std::cout << "Thread is asked to stop\n";
    });

    while (!st.stop_requested()) {
        std::cout << "Start process...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Processed...\n";
    }
    std::cout << "Stopped\n";
}

int main() {
    std::jthread t(heavy_task);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    t.request_stop();
}
