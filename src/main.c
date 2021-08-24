#include "def.h"
#include "fileopts.h"

int main(int argc, char* argv[])
{
    if(check_file(argc, argv) == -1)
    {
        return -1;
    }
    if(init_network() == -1)
    {
        return -1;
    }
    init_task();
    int connectfd = connect(sockfd, (struct sockaddr *)server_addr, sizeof(*server_addr));
    if(connectfd == -1)
    {
        fprintf(stdout, "connect failed\n");
        fprintf(stdout, "IP:[%s], port[%d]\n",inet_ntoa(server_addr->sin_addr), ntohs(server_addr->sin_port));
        return -1;
    }
    fprintf(stdout, ">> established connect, IP:[%s], port[%d]\n",inet_ntoa(server_addr->sin_addr), ntohs(server_addr->sin_port));
    // 发送任务数据信息
    
    sendTaskToServer();
    // 获取服务器反馈信息
    read(sockfd, &vaild, sizeof(char));
    if(vaild == 2)
    {
        fprintf(stdout, "failed to create target file\n");
        return -1;
    }
    else if(vaild == 3)
    {
        fprintf(stdout, "the file has existd\n");
        return -1;
    }
    fprintf(stdout, "===> start file transfer task <===\n");
    // 发送文件数据
    while(task.current < task.total)
    {
        // clearBuf();
        int len = readToBuf();
        sendBufToServer(len);
    }
    fprintf(stdout, "** task completed\n");
    close(connectfd);
    close(sockfd);
    return 0;
}