#include<stdio.h>
#include<time.h>

int main()
{

     // 声明一个time_t变量用于存储时间戳
    time_t timestamp;

    // 获取当前时间戳
    timestamp = time(NULL);

    // 输出时间戳
    printf("当前时间戳: %ld\n", timestamp);

    return 0;
}
