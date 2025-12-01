// re-map existing memory mapping


#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main() {
    size_t pagesize = getpagesize();
    size_t size = pagesize;

    void* p = mmap(nullptr, size, PROT_READ | PROT_WRITE,
                   MAP_SHARED | MAP_ANONYMOUS, -1, 0);  // WHY NOT PRIVATE
    if (p == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    void* p_to = mmap(nullptr, size * 2, PROT_NONE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (p_to == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    strcpy((char*)p, "Hello mmap!");
    std::cout << "Before: " << (char*)p << " " << (size_t)p << " size=" << size << "\n" << (size_t)p << "\n";

    size_t new_size = size * 2;
    void* newp = mremap(p, 0, new_size, MREMAP_MAYMOVE | MREMAP_FIXED, p_to);

    if (newp == MAP_FAILED) {
        perror("mremap");
        munmap(p, size);
        return 1;
    }
    // munmap(p, size);
    strcat((char*)newp, " extended");
    std::cout << "After: " << (char*)newp << " " << " size=" << new_size << "\n" << (size_t)newp << "\n";
    std::cout << "p_to: " << (char*)p_to << " " << " size=" << new_size << "\n" << (size_t)p_to << "\n";

    munmap(newp, new_size);
}
