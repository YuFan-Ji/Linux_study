#include <iostream>
#include <ctype.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <unordered_map>
#include <sys/stat.h>
#include <fcntl.h>

// 一下是全局变量 
// 1. 命令行参数表
#define MAXARGC 128
char *g_argv[MAXARGC];
int g_argc = 0; 

// 2. 环境变量表
#define MAX_ENVS 100
char *g_env[MAX_ENVS];
int g_envs = 0;

// 3. 别名映射表
//std::unordered_map<std::string, std::string> alias_list;

// last exit code 保存最近的退出码
int lastcode = 0;

// 重定向相关
#define NONE_REDIR 0
#define INPUT_REDIR 1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3

int redir = NONE_REDIR;
std::string filename;

// for test
char cwd[1024];
char cwdenv[1024];

// 配置环境变量
void InitEnv()
{
    extern char **environ;
    memset(g_env, 0, sizeof(g_env));
    g_envs = 0;

    //本来要从配置文件来
    //1. 获取环境变量
    for(int i = 0; environ[i]; i++)
    {
        // 1.1 申请空间
        g_env[i] = (char*)malloc(strlen(environ[i])+1);
        strcpy(g_env[i], environ[i]);
        g_envs++;
    }
    g_env[g_envs++] = (char*)"HAHA=for_test"; //for_test
    g_env[g_envs] = NULL;

    //2. 导成环境变量
    for(int i = 0; g_env[i]; i++)
    {
        putenv(g_env[i]);
    }
    environ = g_env;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1. 打印命令行解释器提示信息

#define COMMAND_SIZE 1024    // 数组元素大小
#define FORMAT "[%s@%s %s]# "   // 命令行解释器提示符格式


const char* GetUserName()
{
    const char* name = getenv("USER");
    return name == NULL ? "None" : name;
}


const char* GetHostName()
{
    const char* hostname = getenv("HOSTNAME");
    return hostname == NULL ? "None" : hostname;
}

const char *GetPwd()
{
   //  const char *pwd = getenv("PWD");
   //  return pwd == NULL ? "None" : pwd;
   
    const char *pwd = getcwd(cwd, sizeof(cwd));
    if(pwd != NULL)
    {
        snprintf(cwdenv, sizeof(cwdenv), "PWD=%s", cwd);
        putenv(cwdenv);
    }
    return pwd == NULL ? "None" : pwd;
}

const char *GetHome()
{
    const char *home = getenv("HOME");
    return home == NULL ? "" : home;
}

// 将获取到的pwd截取末尾信息
std::string DirName(const char* pwd)
{
#define SLASH "/"
    std::string dir = pwd;
    // 如果是根目录直接返回
    if (dir == SLASH) return SLASH;
    auto pos = dir.rfind(SLASH);
    if(pos == std::string::npos) return "BUG?";
    return dir.substr(pos+1);
}

// 格式化获取命令行提示符信息
void MakeCommandLine(char cmd_prompt[], int size)
{
    // 这里的 snprintf 作用是按照 FORMAT 变量的格式，将 GetUserName()、GetHostName() 和 GetPwd() 返回的字符串拼接到 cmd_prompt 里，同时确保不会超出 cmd_prompt 的大小 size。
    snprintf(cmd_prompt, size, FORMAT, GetUserName(), GetHostName(), DirName(GetPwd()).c_str());
}

void PrintCommandPrompt()
{
    char prompt[COMMAND_SIZE];
    // 加载提示语句
    MakeCommandLine(prompt, sizeof(prompt));
    printf("%s", prompt);
    // 刷新出来
    fflush(stdout);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2. 获取用户输入的命令

bool GetCommandLine(char *out, int size)
{
    // ls -a -l => "ls -a -l\n" 字符串
    char *c = fgets(out, size, stdin);
    if(c == NULL) return false;
    out[strlen(out)-1] = 0; // 清理\n
    if(strlen(out) == 0) return false;
    return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 3. 命令行分析 "ls -a -l" -> "ls" "-a" "-l"

// 内建命令
// command
bool Cd()
{
    // cd argc = 1
    if (g_argc == 1)
    {
        std::string home = GetHome();
        if (home.empty()) return true;
        chdir(home.c_str());
    }
    else
    {
        std::string where = g_argv[1];
        // cd - / cd ~
        if (where == "-")
        {
            // Todo
        }
        else if (where == "~")
        {
            // Todo
        }
        else
        {
            // chdir(where.c_str()); 这行代码是用来改变当前工作目录的。具体来说，chdir 是一个 C 标准库函数，属于 POSIX（Unix/Linux）系统，用于改变进程的当前工作目录。
            chdir(where.c_str());
        }
    }
    return true;
}

void Echo()
{
    if (g_argc == 2)
    {
        // echo "hello world"
        // echo $?
        // echo $PATH
        std::string opt = g_argv[1];
        if (opt == "$?")
        {
            std::cout << lastcode << std::endl;
            lastcode = 0;
        }
        else if (opt[0] == '$')
        {
            std::string env_name = opt.substr(1);
            const char *env_value = getenv(env_name.c_str());
            if (env_value)
                std::cout << env_value << std::endl;
        }
        else
        {
            std::cout << opt << std::endl;
        }
    }
}



bool CommandParse(char *commandline)
{
#define SEP " "
    g_argc = 0;
    // 命令行分析 "ls -a -l" -> "ls" "-a" "-l"
    g_argv[g_argc++] = strtok(commandline, SEP);
    while((bool)(g_argv[g_argc++] = strtok(nullptr, SEP)));
    g_argc--;
    return g_argc > 0 ? true:false;
}

void PrintArgv()
{
    for(int i = 0; g_argv[i]; i++)
    {
        printf("argv[%d]->%s\n", i, g_argv[i]);
    }
    printf("argc: %d\n", g_argc);
}

// 4. 处理内建命令
bool CheckAndExecBuiltin()
{
     std::string cmd = g_argv[0];
     if(cmd == "cd")
     {
          Cd();
          return true;
                             
     }
     else if(cmd == "echo")
     {
          Echo();
          return true;                         
     }
     else if(cmd == "export")
     {
            
     }
     else if(cmd == "alias")
     {
                   // std::string nickname = g_argv[1];
                   //        // alias_list.insert(k, v);
                   //            
     }
   
     return false;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 5. 执行命令

int Execute()
{
    pid_t id = fork();
    if(id == 0)
    {
        int fd = -1;
        // 子进程检测重定向情况
        if(redir == INPUT_REDIR)
        {
            fd = open(filename.c_str(), O_RDONLY);
            if(fd < 0) exit(1);
            dup2(fd,0);
            close(fd);
        }
        else if(redir == OUTPUT_REDIR)
        {
            fd = open(filename.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0666);
            if(fd < 0) exit(2);
            dup2(fd, 1);
            close(fd);
        }
        else if(redir == APPEND_REDIR)
        {
            fd = open(filename.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0666);
            if(fd < 0) exit(2);
            dup2(fd, 1);
            close(fd);
        }
        else
        {}
        // 进程替换，会影响重定向的结果吗？不影响

        //child
        execvp(g_argv[0], g_argv);
        exit(1);
    }
    int status = 0;
    // father
    pid_t rid = waitpid(id, &status, 0);
    if(rid > 0)
    {   
        // 保存退出状态
        lastcode = WEXITSTATUS(status);
    }
    return 0;
}

void TrimSpace(char cmd[], int &end)
{
    while(isspace(cmd[end]))
    {
        end++;
    }
}

void RedirCheck(char cmd[])
{
    redir = NONE_REDIR;
    filename.clear();
    int start = 0;
    int end = strlen(cmd)-1;

    //"ls -a -l >> file.txt" > >> <
    while(end > start)
    {
        if(cmd[end] == '<')
        {
            cmd[end++] = 0;
            TrimSpace(cmd, end);
            redir = INPUT_REDIR;
            filename = cmd+end;
            break;
        }
        else if(cmd[end] == '>')
        {
            if(cmd[end-1] == '>')
            {
                //>>
                cmd[end-1] = 0;
                redir = APPEND_REDIR;
            }
            else
            {
                //>
                redir = OUTPUT_REDIR;
            }
            cmd[end++] = 0;
            TrimSpace(cmd, end);
            filename = cmd+end;
            break;
        }
        else
        {
            end--;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    while(true)
    {
        // 1. 输出命令行提示符
        PrintCommandPrompt();

        // 2. 获取用户输入的命令
        char commandline[COMMAND_SIZE];
        if(!GetCommandLine(commandline, sizeof(commandline)))
            continue;

        // 3. 命令行分析 "ls -a -l" -> "ls" "-a" "-l"
        if(!CommandParse(commandline))
            continue;
        //PrintArgv();<Paste>
        
        // 4. 检测并处理内键命令
        if(CheckAndExecBuiltin())
            continue;
       
        // 5. 执行命令
        Execute();
    }

    return 0;
}


