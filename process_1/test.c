#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    pid_t p = fork();

    if (p < 0)
    {
        perror("fork!");
        return 1;
    }
    else if (p > 0)
    {
        while(1)
        {
            printf("我是父进程，我的pid是:%d，我的ppid是:%d！\n",getpid(),getppid());
            sleep(1);
        }
    }
    else 
    {
        while(1)
        {
            printf("我是子进程，我的pid是:%d，我的ppid是:%d！\n",getpid(),getppid());
            sleep(1);
        }
    }
    return 0;
}
