#include <iostream>
#include <chrono>
#include <vector>
#include <random>

int main() {
    const int N = 100'000'000;
    std::vector<int> v(N, 1);

    // std::mt19937 rng(0);
    // std::uniform_int_distribution<int> dist(0, 1);
    // for (int i = 0; i < N; i++)
    //     v[i] = dist(rng);


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
