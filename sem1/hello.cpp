#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <sys/ioctl.h>

int main() {
    const char* value = std::getenv("VALUE");
    
    if (value != nullptr) {
        std::cout << "VALUE environment variable: " << value << std::endl;
    } else {
        std::cout << "VALUE environment variable not found." << std::endl;
    }
    
    return 5;
}
