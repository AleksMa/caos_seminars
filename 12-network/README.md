# OSI

## 1. Physical Layer

Просто передача битов, нет инфы про пакеты, логики, гарантий

Примеры: Ethernet twisted pair (1000BASE-T ), Bluetooth, Wi-Fi/4G/5G signals

## 2. Data Link Layer

Адресация между *соседними* устройствами (MAC-address)
Передача фреймов/кадров
Защита от ошибок

Примеры: Ethernet, Wi-Fi

```
ip link show
sudo tcpdump -i eth0 -e
```

## 3. Network Layer

Маршрутизация и адресация через транзитные узлы
Фрагментация пакетов

255.255.255.255
Примеры: IPv4/IPv6, ICMP
IPv4: 2^32
IPv6: 2^128
```
traceroute ya.ru
```

## 4. Transport Layer

Порты (порт ~~ процесс в рамках IP-хоста)
Надежная доставка или быстрая доставкa
Контроль перегрузки, порядок пакетов (TCP)

Примеры: TCP, UDP, QUIC
Порты: 80 (HTTP), 443 (HTTPS), 22 (SSH)

Зачем нужен UDP?

```
ss -tulpn
sudo lsof -i :22
```

## 5. Session Layer

Установление/поддержка сессии, очередности обмена
Повторное подключение
Управление состоянием соединения

Вставка контрольных точек для частичной передачи

Примеры: TLS/WebSocket handshake, RPC сеансы

## 6. Presentation Layer

Форматирование данных
Сериализация
Шифрование/дешифрование

Примеры: TLS/SSL, XML/JSON/Protobuf

## 7. Application Layer

Прикладные протоколы
Смысл данных
Запросы и ответы между приложениями

Примеры: HTTP, DNS, SMTP, IMAP, FTP, SSH, MQTT, WebSocket

––––––

L3/L7 балансеры


# Client / server

Клиенты/серверы и их уровни
Пример: HTTP->TCP->IP


```
nc google.com 80
GET / HTTP/1.1
Host: google.com

```

```
curl google.com
```

```
nc -l 1234

HTTP/1.1 200 OK
Content-Type: text/plain
Content-Length: 13

Hello world, man!
```

# Порт

Две очереди (приходящие и исходящие запросы)
16bit number
0...1023 системные
49152...65535 динамические + эфемерные

```
less /etc/services
```

# DNS

```
cat /etc/hosts
resolvectl query ya.ru
```

# Select vs Poll vs Epoll
