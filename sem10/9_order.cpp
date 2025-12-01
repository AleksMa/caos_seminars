#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <functional>
#include <condition_variable>
#include <semaphore>

using namespace std;

void printFirst() {
    std::cout << "1" << std::endl;
}
void printSecond() {
    std::cout << "2" << std::endl;
}
void printThird() {
    std::cout << "3" << std::endl;
}

class Foo {
public:
    Foo() {
    }

    void first() {
        {
            std::unique_lock lock(mtx_);
            printFirst();
            first_is_done_ = true;
        }
        cv_.notify_one();
    }

    void second() {
        {
            std::unique_lock lock(mtx_);
            cv_.wait(lock, [&]{
                return first_is_done_;
            });

            printSecond();
            second_is_done_ = true;
        }
        cv_.notify_one();
    }

    void third() {
        std::unique_lock lock(mtx_);
        cv_.wait(lock, [&]{
            return second_is_done_;
        });
        printThird();
    }
private:
    bool first_is_done_ = false;
    bool second_is_done_ = false;
    std::condition_variable cv_;
    std::mutex mtx_;
};


int main() {
    Foo foo;

    std::thread t([&] {
        foo.first();
    });

    std::thread t2([&] {
        foo.second();
    });

    foo.third();

    t.join();
    t2.join();
}
