#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
extern char** environ;

/*
 @brief 测试execve函数,需要有new.c文件产生的new,会走else分支;
 * */
int main(int argc, char* argv[])
{
	pid_t pid;
	if((pid = fork()) < 0)
		puts("create child process failed!");
	if(pid == 0)
		execve("new", argv, environ);//不明白什么子进程会走execve分支
	else
		puts("此信息正常输出!");
	return 0;
}
