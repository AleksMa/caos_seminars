#include <signal.h>
#include <stdatomic.h>
#include <stdio.h>
#include <unistd.h>

static volatile sig_atomic_t stop = 0;

static void on_term(int sig) {
    (void)sig;
    stop = 1;
}

int main(void) {
    struct sigaction sa = {0};
    sa.sa_handler = on_term;

    sigemptyset(&sa.sa_mask);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGABRT,  &sa, NULL);
    sigaction(SIGHUP,  &sa, NULL);

    while (!stop) {
        write(2, ".", 1);
        usleep(200000);
    }
    write(2, "\nshutting down cleanly\n", 23);
}
