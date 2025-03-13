#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
    printf("我的程序要运行了!\n");
    //execl("/usr/bin/ls", "ls", "-l", "-a", NULL);
    execl("/usr/bin/top", "top", NULL);
    printf("我的程序运行完毕了\n");
    return 0;
}

