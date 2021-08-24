#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "def.h"

// 传输任务结构
struct Task
{
    int current;
    int total;
    char filename[MAX_FILE_NAME_LEN];
};

// 目标文件路径
char filepath[MAX_FILE_PATH_LEN];
// 目标文件标识符
int fd;
// 目标文件状态指针
struct stat *st;
// 文件内容缓存
char buf[MAX_READ_BUF_LEN];
struct Task task;

void fetch_file_name(char *filename);
int readToBuf();
void clearBuf();