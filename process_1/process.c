#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int id = fork();

    if (id < 0) { 
        perror("fork");
        return 1;
    } 
    else if (id > 0) {  // 父进程
        printf("Parent [%d] is sleeping...\n", getpid());
        sleep(30);
    } 
    else {  // 子进程
        printf("Child [%d] is becoming Z...\n", getpid());
        sleep(5);
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}
