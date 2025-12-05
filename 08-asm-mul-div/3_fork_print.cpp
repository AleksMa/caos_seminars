#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

int main() {
    std::cout << "start ";
    fork();
    std::cout << "end " << std::endl;
}
