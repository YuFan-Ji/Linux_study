#include"progress.h"
#include<unistd.h>
#include<string.h>

#define SIZE 101
#define STYLE '#'     // 定制进度条样式

// v2: 根据下载进度加载进度条
void FlushProcess(const char* tips, double total, double current)
{
    const char* lable = "|/-\\";
    int len = sizeof(lable);

    static int index = 0;    // 定义静态变量，外部每一次调用FlushProcess，lable都会旋转

    char buffer[SIZE];       // 初始化buffer
    memset(buffer, 0, sizeof(buffer));

    double rate = current * 100.0 / total;            // 当前下载进度，是一个百分数，因此要乘100
    int num = (int)rate;              // 进度条'#'的数量就是ret取整

    int i = 0;
    for (; i < num; i++)
    {
        buffer[i] = STYLE;          // 将进度条大小加载入buffer
    }
    
    // 进行输出
    printf ("[%s][%-100s][%.1lf%%][%c]\r", tips, buffer, rate, lable[index++]);
    fflush(stdout);
    index = index % len;

    if (num >= 100) printf("\n");
}


// v1: 展示进度条基本功能
void process()
{
    // 进度条样子 [######...][n%][旋转|]
    int rate = 0;        // 统计进度n%
    char buffer[SIZE];   // buffer作为一个缓冲，存储我们当前进度条
    memset(buffer, 0, sizeof(buffer));   // 初始化buffer为\0方便我们进行每一次插入，控制输出大小
    const char* lable = "|/-\\";      // 初始化我们加载过程中旋转的动态效果，一共是|/-\四种状态，其中\需要用转义字符
    int len = sizeof(lable);    // 计算lable长度，以便后序使用

    // 开始循环输出进度条
    while (rate <= 100)         // 循环输出至100%
    {
        printf("[%-100s][%d%%][%c]\r", buffer, rate, lable[rate % len]);  // 这里面要注意的是%符号的输出要这样写%%
        //，其次\r使得光标回去，-100s保证左对齐并且预留空位
        
        fflush(stdout);   // 把我们的输出刷新出去

        buffer[rate] = STYLE;    // 更新进度条
        rate++;

        usleep(100000);          // 设定进度条加载时间
    }

    printf("\n");         // 防止命令行吞了进度条，换行

}
