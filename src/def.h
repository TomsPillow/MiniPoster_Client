#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define DEFAULT_PORT 3333
#define MAX_LISTEN_QUEUE 10
#define MAX_FILE_PATH_LEN 1024
#define MAX_FILE_NAME_LEN 1024
#define IP_LEN 40
#define MAX_READ_BUF_LEN 1024

unsigned int recvbuf_len;
char IP[IP_LEN];

int sockfd;
struct sockaddr_in *server_addr;
int vaild;

// util.c
int check_file(int argc, char* argv[]);
int init_network();
int init_task();
int sendBufToServer(int len);
int sendTaskToServer();