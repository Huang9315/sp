#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void print_george() {    // 每隔一秒鐘印出一次 George 的函數
    while (1) {    
        printf("George\n");    
        sleep(1);    
    }    
}    

void print_mary() {     // 每隔2秒鐘印出一次 Mary 的函數
    while (1) {    
        printf("Mary\n");    
        sleep(2);    
    }    
}    

int main() {     // 主程式開始
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 < 0) {  // 檢查 fork 是否成功
        perror("Failed to fork");
        return 1;
    } else if (pid1 == 0) {  // 子進程1
        print_george();
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {  // 檢查 fork 是否成功
        perror("Failed to fork");
        return 1;
    } else if (pid2 == 0) {  // 子進程2
        print_mary();
        exit(0);
    }

    while (1) {     // 主程式每隔一秒鐘
        printf("----------------\n");    // 就印出分隔行
        sleep(1);     // 停止一秒鐘
    }    

    return 0;    
}
