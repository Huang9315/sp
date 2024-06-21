# 多執行緒提款與存款程式

這個專案包含兩個版本的多執行緒提款與存款程式：
1. 沒有使用互斥鎖的版本，會造成 race condition。
2. 使用互斥鎖的版本，避免 race condition。

## 編譯和運行

### 編譯

使用 `gcc` 編譯：

```sh
gcc -o no_mutex no_mutex.c -pthread
gcc -o with_mutex with_mutex.c -pthread
