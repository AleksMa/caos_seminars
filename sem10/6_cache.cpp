#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>
#include <iostream>

class THashMap {
private:
    std::unordered_map<int, int> data_;

    mutable std::shared_mutex mtx_;

public:
    void Erase(int key) {
        // std::lock_guard<std::shared_mutex> lg(mtx_);
        // std::unique_lock l(mtx_);
        std::unique_lock<std::shared_mutex> l(mtx_);
        data_.erase(key);
    }

    void Set(int key, int value) {
        std::unique_lock<std::shared_mutex> l(mtx_);
        data_[key] = value;
    }

    int Get(int key) const {
        std::shared_lock<std::shared_mutex> l(mtx_);
        if (!data_.count(key)) {
            return 0;
        }
        return data_.at(key);
    }

    bool Exist(int key) const {
        std::shared_lock<std::shared_mutex> l(mtx_);
        return data_.count(key);
    }
};

int main() {
    THashMap map;

    std::thread t([&] {
        map.Set(42, 42);
    });

    std::thread t2([&] {
        map.Get(1337);
    });

    std::thread t3([&] {
        map.Set(1337, 1337);
    });

    {
       map.Get(42);
    }

    t.join();
    t2.join();
    t3.join();
}
