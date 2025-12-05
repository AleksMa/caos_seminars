#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>


int main() {
    umask(0000);
    int fd = open("demo", O_CREAT|O_RDWR, 0666);
    getchar();
    unlink("demo");
    ftruncate(fd, 4096);

    char *p = (char*)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(p, "Hello world!\n");
    msync(p, 4096, MS_SYNC);

    printf("%s\n", p);

    getchar();

    close(fd);
    munmap(p, 4096);
}
