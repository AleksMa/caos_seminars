#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

std::queue<int> q;

std::mutex m;
std::condition_variable cv;
bool done = false;

void producer() {
    for (int i = 1; i <= 10; ++i) {
        {
            std::lock_guard<std::mutex> lk(m);
            q.push(i);
            std::cout << "[producer] pushed " << i << "\n";
        }

        cv.notify_one();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    {
        std::lock_guard<std::mutex> lk(m);
        done = true;
        std::cout << "[producer] done" << std::endl;
    }
    cv.notify_all();
}

// variable – spurious wakeup, logic check...
// mutex – sleep, sync

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lk(m);

        // cv.wait(lk, [] {
        //     return !q.empty() || done;
        // });

        while (q.empty() && !done) {
            cv.wait(lk);
        }

        // mutex is still locked here

        // if (q.empty() && !done)
        //     cv.wait(lk);

        // std::cout << "[consumer " << id << "] unlocked" << std::endl;

        if (q.empty()) {
            std::cout << "[consumer " << id << "] no more data, exiting" << std::endl;
            break;
        }

        int value = q.front();
        q.pop();

        lk.unlock();

        std::cout << "[consumer " << id << "] got " << value << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void noisy_notifier() {
    // for (int i = 0; i < 1000; ++i) {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(50));
    //     cv.notify_all();
    // }
}

int main() {
    std::thread prod(producer);

    std::thread c1(consumer, 1);
    // std::thread c2(consumer, 2);
    std::thread noise(noisy_notifier);

    prod.join();
    c1.join();
    // c2.join();
    noise.join();

    std::cout << "All threads finished\n";
    return 0;
}
