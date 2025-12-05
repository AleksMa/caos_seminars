#include <cstdio>
#include <cstdlib>
#include <sys/mman.h>
#include <cstring>

int main(int argc, char** argv) {
    size_t size = 2ULL * 1024 * 1024 * 1024;

    char* ptr = static_cast<char*>(std::malloc(size));

    getchar();

    if (argc > 1) {
        for (size_t i = 0; i < size; ++i) {
            ptr[i] = '1';
        }
        getchar();
    }
}
