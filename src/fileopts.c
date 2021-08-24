#include "fileopts.h"

void fetch_file_name(char *filename)
{
    int index = strlen(filepath) - 1;
    while(filepath[index] != '/' && index >= 0)
    {
        index--;
    }
    if(index == -1)
    {
        // 使用当前目录下的相对路径的情况
        strcpy(filename, filepath);
        return ;
    }
    strcpy(filename, filepath + index + 1);
}

int readToBuf()
{
    // clearBuf();
    ssize_t len = read(fd, buf, MAX_READ_BUF_LEN);
    return len;
}

void clearBuf()
{
    memset(buf, 0, MAX_READ_BUF_LEN);
}