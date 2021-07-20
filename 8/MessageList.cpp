#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

/*
*@FuncName  int msgget(key_t key, int msgflg);
*@brief     创建一个新的消息队列或打开一个已经存在的消息队列
*@param[in] key_t key:表示所创建的消息队列的键值
*@param[in] int msgflg:设置消息队列的访问权限
*@return    如果函数调用成功,返回值为与参数key相关联的标识符;如果调用失败则返回-1
*/

/*
*@FuncName  int msgsnd(int msqid, const void* msgp, size_t msgsz, int msgflg);
*@brief     向消息队列发送消息
*@param[in] 将信息发送到消息队列的标识符
*@param[in] 指向要发送的消息数据
*@param[in] 以字节数表示消息数据长度
*@param[in] 消息队列满时的处理方法,该参数可以为0或者IPC_NOWAIT;如果消息队列已满,msgflg参数没有设置IPC_NOWAIT值,则msgsnd函数将阻塞,
            如果设置了IPC_NO值,则msgsnd函数调用失败,并返回-1,知道消息队列有空间,才返回0
*@return    调用成功时,返回值为0;如果失败,则返回-1
*/

/*
*@FuncName  ssize_t msgrcv(int msqid, void* msgp, size_t msgsz, long msgtyp, int msgflg)       
*@brief     接收消息队列中的消息数据
*@param[in] 从msqid标识符所代表的消息队列中接收信息
*@param[in] 指向存放消息数据的内存空间
*@param[in] 以字节数表示消息数据长度
*@param[in] 读取的消息数据类型
*@param[in] 对读取的消息数据不满足情况时的处理;
*@return    成功返回0;失败返回-1
*/

/*
*@FuncName  int msgctl(int msqid, int cmd, struct msqid_ds* buf)
*@brief     对消息队列的控制操作
*@param[in] msqid标识需要控制的消息队列
*@param[in] 控制内容
*@param[in] 指向需要执行控制操作的消息队列
*@return    
*/

int main(void)
{
    key_t key;
    int proj_id = 1;
    int msqid;
    char message1[] = {"Hello Linux"};
    char message2[] = {"Hello Windows"};

    struct msgbuf
    {
        long msgtype;
        char msgtext[1024];
    }snd,rcv;

    key = ftok("/home/cff/2", proj_id);
    if(key == -1)                                               //创建新进程
    {
        perror("create key error!\n");
        return 1;
    }
    if((msqid = msgget(key, IPC_CREAT | 0666)) == -1)           //创建消息队列
    {
        printf("magget error!\n");
        exit(1);
    }
    snd.msgtype = 1;
    sprintf(snd.msgtext, message1);
    if(msgsnd(msqid, (struct msgbuf*)&snd, sizeof(message - 1) + 1, 0) == -1)
    {
        printf("msgsnd error!\n");
        exit(1);
    }

    snd.msgtype = 2;
    sprintf(snd.msgtext, "%s", message2);
    if(msgsnd(msqid, (struct msgbuf*)&snd, sizeof(message2) + 1, 0) == -1)
    {
        printf("msgrcv error!\n");
        exit(1);
    }
    if(msgrcv(msqid, (struct msgbuf*)&rcv, 80, 1, IPC_NOWAIT) == -1)
    {
        printf("msgrcv error!\n");
        exit(1);
    }
    printf("the received message:%s.\n", rcv.msgtext);

    system("ipcs -q");
    exit(0);
}