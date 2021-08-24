#include "def.h"
#include "fileopts.h"
#include <errno.h>

// 验证文件信息
int check_file(int argc, char* argv[])
{
    fprintf(stdout, "** initializing file info\n");
    if(argc == 5)
    {
        for(int i = 1; i < argc; i = i + 2)
        {
            if(strcmp(argv[i], "-f") == 0)
            {
                strcpy(filepath, argv[i + 1]);
            }
            else if(strcmp(argv[i], "-a") == 0)
            {
                strcpy(IP, argv[i + 1]);
            }
        }
    }
    else
    {
        fprintf(stdout, "wrong argument number\n");
    }
    st = (struct stat *)malloc(sizeof(struct stat));
    // if((fd = open(filename, O_RDONLY)) == -1)
    if(stat(filepath, st) == -1)
    {
        fprintf(stdout, "wrong file name:[%s], please check it out\n", filepath);
        fprintf(stdout, "errno = %d\n", errno);
        return -1;
    }
    fprintf(stdout, ">> fetched target file:[%s]\n", filepath);
    fprintf(stdout, ">> total size:[%lldB]\n", st->st_size);
    fd = open(filepath, O_RDONLY);
    return 0;
}

// 初始化网络信息
int init_network()
{
    fprintf(stdout, "** initializing network info\n");
    // 采用IPv4协议，TCP数据流套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        fprintf(stdout, "the setup of socket failed\n");
        return -1;
    }
    fprintf(stdout, ">> socket was established\n");
    fprintf(stdout, ">> Destinate IP:[%s] Port:[%d]\n", IP, DEFAULT_PORT);
    // 指定套接字目标地址，端口，协议簇
    server_addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    // memset(&server_addr, 0, sizeof(server_addr));
    server_addr->sin_addr.s_addr = inet_addr(IP);
    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(DEFAULT_PORT);
    // fprintf(stdout, ">> in network, Destinate IP:[%x] Port:[%x]\n", server_addr->sin_addr.s_addr, server_addr->sin_port);
    return 0;
}

// 初始化任务信息
int init_task()
{
    fprintf(stdout, "** initializing task\n");
    task.current = 0;
    task.total = st->st_size;
    memset(task.filename, 0, sizeof(task.filename));
    fetch_file_name(task.filename);
    fprintf(stdout, ">> task was established\n");
    return 0;
}

// 发送缓存至服务器
int sendBufToServer(int len)
{
    write(sockfd, buf, len);
    task.current = task.current + len;
    fprintf(stdout, ">> current:[%dB]    total:[%dB]\n", task.current, task.total);
    return 0;
}

// 发送任务数据至服务器
int sendTaskToServer()
{
    char bytes[4];
    bytes[0] = task.total;
    bytes[1] = task.total >> 8;
    bytes[2] = task.total >> 16;
    bytes[3] = task.total >> 24;
    // 发送文件名
    write(sockfd, task.filename, sizeof(task.filename));
    // 发送文件大小
    write(sockfd, bytes, sizeof(4));
    return 0;
}
