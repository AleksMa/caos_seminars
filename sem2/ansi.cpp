#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main() {
    if (ioctl(STDOUT_FILENO, TCGETS) == 0) {
        std::cout << "\x1b[1;3;33;41mTerminal\x1b[0m is here" << std::endl;
    } else {
        std::cout << "Not terminal: " << std::endl;
    }

    return 0;
}
