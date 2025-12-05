#include <stdio.h>

int main() {
    unsigned int x = 0x11223344;
    unsigned char *p = (unsigned char *)&x;

    for (int i = 0; i < 4; i++)
        printf("byte %d: %x\n", i, p[i]);
}
