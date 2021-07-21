#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/*
*@FuncName  __pid_t fork (void) __THROWNL;
*@brief     通过系统调用,返回一个一模一样进程;在父进程中,fork()返回子进程的pid值,在子进程中,fork()返回0 
*/
int main()
{
    pid_t pid;
    if((pid = fork()) < 0)          //创建进程失败
    {
        printf("fork error!\n");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("in the child process!\n");
    }
    else
    {
        printf("in the parent process!\n");
    }
    exit(0);
}