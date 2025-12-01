#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

void* worker(void*)
{
    return nullptr;
}

int main()
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    pthread_attr_setguardsize(&attr, 0);

    pthread_t tid;
    int count = 0;

    while (1) {
        ++count;
        int err = pthread_create(&tid, &attr, worker, nullptr);
        if (err != 0) {
            break;
        }
    }

    std::cout << "Создано потоков: " << count << std::endl;

    return 0;
}
