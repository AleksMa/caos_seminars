#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static void on_signal(int sig) {
    const char *name = strsignal(sig);
    dprintf(STDERR_FILENO, "[%d] caught %s (%d)\n", getpid(), name, sig);
}

int main(void) {
    struct sigaction sa = {0};
    sa.sa_handler = on_signal;

    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGHUP,  &sa, NULL);
    sigaction(SIGKILL,  &sa, NULL);
    sigaction(SIGABRT,  &sa, NULL);
    sigaction(SIGHUP,  &sa, NULL);

    dprintf(2, "[%d] running; press Ctrl-C or send SIGTERM/SIGHUP\n", getpid());
    for (;;) pause();
}
