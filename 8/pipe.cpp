#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define MAXSIZE 100

int main(void)
{
	int fd[2], pid, line;
	char message[MAXSIZE];
	/*创建管道*/
	if(pipe(fd) == -1)
	{
		perror("create pipe failed");
		return 1;
	}
	/*创建新进程*/
	else if((pid = fork()) < 0)
	{
		perror("not create a new process");
		return 1;
	}
	/*子进程*/
	else if(pid == 0)
	{
		close(fd[0]);				/*关闭读端*/
		printf("child process send message!\n");
		write(fd[1], "Welcome to Linux!", 17);
	}
	else
	{
		close(fd[1]);				/*关闭写端*/
		printf("parent process receive message is:\n");
		line = read(fd[0], message, MAXSIZE);	/*读取消息*/
		write(STDOUT_FILENO, message, line);	/*将消息写入终端*/
		printf("\n");
		wait(NULL);
		_exit(0);
	}
	return 0;
}
