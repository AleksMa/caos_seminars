#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

int main() {
    int x = 100;

    pid_t pid = fork();
    if (pid == 0) {
        sleep(1);
        std::cout << "[Child] x = " << x << std::endl;
        _exit(42);
    }

    x = 1000;
    std::cout << "[Parent] x = " << x << std::endl;

    int* status;
    wait(status);
    std::cout << "status = " << *status << std::endl;
}
