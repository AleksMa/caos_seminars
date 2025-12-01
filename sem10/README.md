## Locks

### std::lock_guard

no lock / unlock

### std::scoped_lock

no lock / unlock
several mutexes safe lock

### std::unique_lock

lock / unlock
movable

### std::shared_lock

lock / unlock
movable

for shared_mutex

## deadlock avoidence

```c++
std::scoped_lock lock(m1, m2);
```

old style
```c++
std::lock(e1.m, e2.m);
std::lock_guard<std::mutex> lk1(e1.m, std::adopt_lock);
std::lock_guard<std::mutex> lk2(e2.m, std::adopt_lock);
```

unique_lock
```c++
std::unique_lock<std::mutex> lk1(e1.m, std::defer_lock);
std::unique_lock<std::mutex> lk2(e2.m, std::defer_lock);
std::lock(lk1, lk2);
```

## Condition variable

Thread A                             Thread B
--------------------------------     --------------------
if (!ready.load())   // sees false
                                      ready.store(true);
                                      notify();
sleep();    // too late


```c++
std::unique_lock lk(m);
cv.wait(lk, []{
    return flag;
});
```

или

```c++
std::unique_lock lk(m);
while(!flag) {
    cv.wait(lk);
}
```
