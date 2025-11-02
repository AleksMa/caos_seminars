#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>

void print_red_if_tty(const char *s) {
    struct termios t;
    int is_tty = (ioctl(STDOUT_FILENO, TCGETS, &t) == 0);

    if (is_tty) {
        // красный текст + сброс
        printf("\x1b[31m%s\x1b[0m", s);
    } else {
        // просто текст без escape-кодов
        printf("%s", s);
    	printf("\x1b[31m%s\x1b[0m", s);
    }
}

int main() {
    print_red_if_tty("Hello, world!\n");
    return 0;
}
