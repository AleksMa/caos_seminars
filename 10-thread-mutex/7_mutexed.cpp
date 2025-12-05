#include <mutex>
#include <thread>
#include <vector>
#include <iostream>

template <typename T, class Mutex = std::mutex>
class Mutexed {
    // Define your own OwnerRef
    class OwnerRef {
    private:
        T* obj_ref_;
        std::unique_lock<Mutex> lg_;
    public:
        OwnerRef(T* obj, Mutex& mutex)
        : obj_ref_(obj)
        , lg_(mutex)
        {
        }

        T* operator->() {
            return obj_ref_;
        }
        T& operator*() {
            return *obj_ref_;
        }
    };

public:
    template <typename... Args>
    explicit Mutexed(Args&&... args)
        : object_(std::forward<Args>(args)...) {
    }

    OwnerRef Acquire() {
        return OwnerRef(&object_, mutex_); // Your code goes here
    }

private:
    T object_;
    Mutex mutex_; // Guards access to object_
};

template <typename T>
auto Acquire(Mutexed<T>& object) {
    return object.Acquire();
}

int main() {
    Mutexed<std::vector<int>> mut;

    std::thread t([&] {
        auto g = mut.Acquire();
        g->push_back(42);
    });

    std::thread t2([&] {
        auto g = mut.Acquire();
        g->push_back(1337);
    });

    {
        auto g = mut.Acquire();
        g->push_back(1453);
    }

    t.join();
    t2.join();

    for (const auto& el : *mut.Acquire()) {
        std::cout << el << std::endl;
    }
}
