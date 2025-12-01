#include <iostream>
#include <chrono>
#include <vector>

int main() {
    const int N = 100'000'000;
    std::vector<int> v(N, 1);

    int sum = 0;
    auto t1 = std::chrono::high_resolution_clock::now();

    for (int x : v) {
        if (x == 1) {
            sum += x;
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << sum << "\n";
    std::cout << "Time: " << (t2 - t1).count() / 1e6 << " ms\n";
}
