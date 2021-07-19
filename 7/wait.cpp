#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*定义一个功能函数,通过返回的状态,判断进程是正常退出还是信号导致退出*/

void exit_s(int status)
{
    if(WIFEXITED(status))               //这个宏用来指出子进程是否为正常退出的，如果是，它会返回一个非零值
        printf("normal exit, status = %d\n", WEXITSTATUS(status));  //这个宏用来指出子进程是否为正常退出的，如果是，它会返回一个非零值
    else if (WIFSIGNALED(status))
        printf("signal exit! status = %d\n", WTERMSIG(status)); //取出的字段值就是信号的编号
}
/*
@brief 测试wait函数
*/
int main(void)
{
    pid_t pid, pid1;
    int status;
    if((pid = fork()) < 0)
    {
        printf("child process error!\n");
        exit(0);
    }
    else if(pid == 0)
    {
        printf("the child process!\n");
        exit(2);
    }
    if(wait(&status) != pid)
    {
        printf("this is a parent process!\nwait error!\n");
        exit(0);
    }
    exit_s(status);
    if(pid = fork() < 0)
    {
        printf("child process error!\n");
        exit(0);
    }
    else if(pid == 0)
    {
        printf("the child process!\n");
        pid1 = getpid();
        /*使用kill()函数发送信号*/
        kill(pid1, 19);                 //终止进程
    }
    if(wait(&status) != pid)
    {
        printf("this is a parent process!\nwait error!\n");
        exit(0);
    }
    exit_s(status);
    exit(0);
}