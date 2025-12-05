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
        printFirst();
        sm1.release();
    }

    void second() {
        sm1.acquire();
        printSecond();
        sm2.release();
    }

    void third() {
        sm2.acquire();
        printThird();
    }
private:
    std::binary_semaphore sm1{0};
    std::binary_semaphore sm2{0};
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
