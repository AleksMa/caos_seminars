#include <unistd.h>

int main() {
    const char msg[] = "Hello via syscall!\n";
    write(1, msg, sizeof(msg) - 1);  // 1 = stdout
    return 0;
}
