#include <atomic>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

struct Account {
    int balance;
    std::mutex mtx;
};

void transfer(Account& from, Account& to, int amount) {
    // {
    //     lock_guard l(from.mtx);
    //     from.balance -= amount;
    // }
    // std::lock(from.mtx, to.mtx);
    // std::lock_guard lg1(from.mtx, std::adopt_lock);
    // std::lock_guard lg2(to.mtx, std::adopt_lock);

    std::scoped_lock sl(from.mtx, to.mtx);

    if (from.balance <= 0) {
        return;
    }

    {
        // std::lock_guard<std::mutex> lock(from.mtx);
        from.balance -= amount;
    }
    {
        // std::lock_guard<std::mutex> lock(to.mtx);
        to.balance += amount;
    }
}

int main() {
    Account a{.balance = 1000};
    Account b{.balance = 1000};

    std::thread t1([&] {
        for (int i = 0; i < 1000000; ++i) {
            transfer(a, b, 1);
            if (i % 1000 == 0) {
                std::cout << "a->b" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    });

    std::thread t2([&] {
        for (int i = 0; i < 1000000; ++i) {
            transfer(b, a, 1);
            if (i % 1000 == 0) {
                std::cout << "b->a" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    });

    t1.join();
    t2.join();

    std::cout << "a.balance = " << a.balance << "\n";
    std::cout << "b.balance = " << b.balance << "\n";
}
