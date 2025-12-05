#include <stdio.h>
extern "C" long add_two(long, long);

int main(void) {
    printf("%ld\n", add_two(2, 40));
    return 0;
}
