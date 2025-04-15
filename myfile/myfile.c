#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
     umask(0);
     int fd = open("log1.txt", O_WRONLY | O_CREAT, 0666);
      if(fd < 0) exit(1);

      dup2(fd, 1);


      char buffer[64] = "你好我是重定向";
      printf("%s\n", buffer);
      
     close(fd);
    // close(1);
    // int fd = open("log1.txt", O_WRONLY|O_CREAT, 00644);
    // if(fd < 0){
    // perror("open");
    // return 1;
    // }
    // printf("fd: %d\n", fd);
    // fflush(stdout);
    // close(fd);
    // exit(0);
//    int fd = open("log2.txt", O_RDONLY);
//    if (fd < 0)
//    {
//        perror("open");
//        return 1;
//    }
//
//    char buff[100];
//    read(fd, buff, sizeof(buff) - 1);
//
//    close(fd);
//
//    printf("%s\n", buff);
//    return 0;
//
//    int fd1 = open("log1.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);    
//    int fd2 = open("log2.txt", O_CREAT | O_WRONLY | O_APPEND, 0666);
//    // int fd3 = open("log2.txt", O_RDONLY);
//
//    if(fd1 < 0)
//    {
//        perror("open");
//        return 1;
//    }
//    printf("fd1: %d\n", fd1);
//  
//    if(fd2 < 0)
//    {
//        perror("open");
//        return 1;
//    }
//    printf("fd2: %d\n", fd2);
//    
//    // 使用 write() 写入内容到 log1.txt（覆盖原内容）
//    // char *text1 = "Hello, this is log1.txt\n";
//    // write(fd1, text1, strlen(text1));
//
//    // 使用 write() 追加内容到 log2.txt（不会覆盖原内容）
//    char *text2 = "aaaaaaaaaaaaaaaaaaaaaaaa\n";
//    write(fd2, text2, strlen(text2));
//
//    // 关闭文件
//    // close(fd1);
//    close(fd2);
//    close(fd3);
//
//    return 0;
}
