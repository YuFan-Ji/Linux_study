#include"progress.h"
#include<time.h>
#include<unistd.h>
#include<stdlib.h>

// 定义函数指针，以便于自定义回调函数
typedef void(*call_t)(const char*, double, double);

int total = 1024;    // 定义总下载量
double speed[] = {1, 5, 0.3, 0.5, 0.03, 0.01};      // 设计下载速度，用这几个double模拟网速的变化

// 下载，回调函数
void download(int total, call_t cb)     // total 下载总量，cb刷新策略
{
    srand(time(NULL));        // 设计随机数种子

    double current = 0.0;     // 设置当前下载量，初始化为0

    while (current <= total)
    {
        cb("下载中...", total, current);    // 进行函数回调，进度条刷新策略

        if (current >= total) break;
        // 下载代码
        usleep(1500);      // 模拟下载过程
        int len = sizeof(speed);
        int random = rand() % len;     // 设置随机数
        current += speed[random];      // 下载对应网速的大小

        if (current > total) current = total;    // 如果下载到最后直接超过了100%的话，就重新设置一下current以便于加载出100%的状态
    }

}


// 上传，回调函数
void uploadload(int total, call_t cb)     // total 下载总量，cb刷新策略
{
    srand(time(NULL));        // 设计随机数种子

    double current = 0.0;     // 设置当前下载量，初始化为0

    while (current <= total)
    {
        cb("上传中...", total, current);    // 进行函数回调，进度条刷新策略

        if (current >= total) break;
        // 上传代码
        usleep(1500);      // 模拟上传过程
        int len = sizeof(speed);
        int random = rand() % len;     // 设置随机数
        current += speed[random];      // 下载对应网速的大小

        if (current > total) current = total;    // 如果下载到最后直接超过了100%的话，就重新设置一下current以便于加载出100%的状态
    }

}

int main()
{
   // process();
   
    download(1024.0, FlushProcess);
    printf("download 1024.0MB done\n");
    download(512.0, FlushProcess);
    printf("download 512.0MB done\n");
    download(256.0,FlushProcess);
    printf("download 256.0MB done\n");
    download(128.0,FlushProcess);
    printf("download 128.0MB done\n");
    download(64.0,FlushProcess);
    printf("download 64.0MB done\n");
    uploadload(256.0,FlushProcess);
    printf("uploadload 256.0MB done\n");
    uploadload(128.0,FlushProcess);
    printf("uploadload 128.0MB done\n");
    return 0;
}
