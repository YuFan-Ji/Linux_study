#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// 定义函数指针类型
typedef void (*handler_t)();

// 临时任务函数1
void fun_one() {
    printf("这是一个临时任务1\n");
}

// 临时任务函数2
void fun_two() {
    printf("这是一个临时任务2\n");
}

// 函数指针数组，用于存储所有临时任务
handler_t handlers[2];

// 加载任务
void Load() {
    handlers[0] = fun_one;
    handlers[1] = fun_two;
}

// 执行所有临时任务
void handler() {
    if (handlers[0] == NULL)  // 如果任务列表为空，则加载任务
        Load();
    
    // 执行所有任务
    int i = 0;
    for (; i < 2; i++) {
        if (handlers[i] != NULL) {
            handlers[i]();  // 调用任务函数
        }
    }
}

int main() {
    pid_t pid;
    pid = fork();  // 创建子进程

    if (pid < 0) {
        printf("创建子进程失败\n");
        return 1;
    } else if (pid == 0) {  // 子进程
        printf("子进程正在运行，子进程ID：%d\n", getpid());
        sleep(5);  // 子进程休眠5秒
        exit(1);   // 子进程退出，返回退出码1
    } else {  // 父进程
        int status = 0;
        pid_t ret = 0;

        do {
            ret = waitpid(-1, &status, WNOHANG);  // 非阻塞式等待子进程退出
            if (ret == 0) {
                printf("子进程仍在运行\n");  // 如果子进程未退出
            }
            handler();  // 执行临时任务
        } while (ret == 0);  // 如果子进程未退出，继续循环

        if (WIFEXITED(status) && ret == pid) {
            printf("成功等待子进程退出，子进程返回码：%d\n", WEXITSTATUS(status));
        } else {
            printf("等待子进程失败\n");
            return 1;
        }
    }

    return 0;
}






//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/wait.h>
//#include <unistd.h>
//
//int main() {
//    pid_t pid;
//    int status;
//
//    // 创建子进程
//    pid = fork();
//
//    if (pid == -1) {
//        // 如果创建子进程失败，打印错误并退出
//        perror("fork failed");
//        exit(1);
//    }
//
//    if (pid == 0) {
//        // 子进程代码
//        printf("这是子进程，进程ID：%d\n", getpid());
//        // 子进程正常退出
//        exit(42);
//    } else {
//        // 父进程代码
//        printf("这是父进程，等待子进程退出...\n");
//
//        // 使用 waitpid 等待子进程退出，并获取退出状态
//        pid_t child_pid = waitpid(pid, &status, 0);
//
//        // 判断子进程是否正常退出
//        if (child_pid == -1) {
//            // 如果 waitpid 出错，打印错误信息
//            perror("waitpid failed");
//            exit(1);
//        }
//
//        // 判断子进程是否正常退出
//        if (WIFEXITED(status)) {
//            printf("子进程正常退出，退出码：%d\n", WEXITSTATUS(status));
//        } else {
//            printf("子进程未正常退出。\n");
//        }
//
//        printf("父进程结束，进程ID：%d\n", getpid());
//    }
//
//    return 0;
//}
//
//
////#include <stdio.h>
//#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/wait.h>
//#include <unistd.h>
//
//int main() {
//    pid_t pid = fork(); // 创建子进程
//    int status;
//
//    if (pid == 0) {  // 子进程
//        printf("子进程：正在运行...\n");
//        sleep(2); // 模拟任务
//        printf("子进程：退出。\n");
//        exit(42); // 退出码 42
//    }
//
//
//    wait(&status);
//    printf("进程 %d：wait() 返回，子进程退出码：%d\n", getpid(), WEXITSTATUS(status));
//
//    return 0;
//}
//


//#include <stdio.h>
//#include <errno.h>
//#include <string.h>
//
//int main()
//{
//    int i = 0;
//    for (; i < 200; i++)
//    {
//        printf("strerror(%d):%s\n",i, strerror(i));
//    }
//
//    return 0;
//}
//
//int main() {
 //   FILE *file = fopen("nonexistent.txt", "r"); // 尝试打开一个不存在的文件
 //   if (!file) {
 //       printf("Error: %s\n", strerror(errno)); // 输出对应的错误信息
 //   }
 //   return 1; // 返回一个非零退出码
//}
