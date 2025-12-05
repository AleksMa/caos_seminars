#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t x = 0x11223344;
    FILE *f = fopen("out.bin", "wb");
    fwrite(&x, sizeof(x), 1, f);
    fclose(f);
}
