#include <sys/resource.h>
#include <iostream>

int COUNTER = 0;

void f() {
    std::cout << ++COUNTER << std::endl;
    f();
    f();
}

int main() {
    rlimit rl{};
    rl.rlim_cur = 10 * 1024 * 1024;
    rl.rlim_max = 10 * 1024 * 1024;

    if (setrlimit(RLIMIT_STACK, &rl) != 0) {
        perror("setrlimit");
    }

    getrlimit(RLIMIT_STACK, &rl);
    std::cout << "Stack limit: " << rl.rlim_cur / 1024 / 1024 << " KiB\n";

    // f();
}
