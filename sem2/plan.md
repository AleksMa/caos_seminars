# Sem 2

## Quiz

https://forms.yandex.ru/u/68cad9c602848f1fd08abc81

ТЫ/ВЫ обсудить

## Grep

1. alias | grep grep
Как задавать alias
2. grep —always
cat text.txt | grep mem | grep 23
cat text.txt | grep --color=always mem | grep 23
3. написать программу с isatty / ioctl
```cpp
int main() {
    if (isatty(STDOUT_FILENO) == 0) {
        std::cout << "Terminal " << std::endl;
    } else {
        std::cout << "Not terminal: " << (errno == ENOTTY) << std::endl;
    }
    
    return 0;
}```
4. strace -e ioctl
5. ltrace -e isatty
6. рассказать про ANSI- цвета
```bash
"\x1b[1;3;33;41mHello\x1b[0m world "
```

Рассказать про галки ввода-вывода

## Еще про сисколы

Повыводить "hello world" 1-4 раза
Сколько сисколов

## stdin / stdout

Написать прогу которая читает из stdout и пшиет в stdout сразу

## files

```bash
ls -al /proc/$(pidof fs)/fd
```

почему важно закрывать fd (ограниченное количество)


## dup

fd2 = fd1 

один и тот же ФД

dup2(fd1, fd2)
