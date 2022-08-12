#include "directory.h"
#include <string.h>

static char filename[128][256];
static int len = 0;

int get_dir_files(char* path, int depth ,char (**file)[][256], int *count)
{
    int ret = trave_dir(path, depth);
    if (0 == ret)
    {
        *count = len;
        *file = &filename;
    }
    return ret;
}

int trave_dir(char* path, int depth)
{
    DIR* d; //声明一个句柄
    struct dirent* file; //readdir函数的返回值就存放在这个结构体中
    struct stat sb;

    if (!(d = opendir(path)))
    {
        printf("error opendir %s!!!/n", path);
        return -1;
    }
    while ((file = readdir(d)) != NULL)
    {
        //把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录
        if (strncmp(file->d_name, ".", 1) == 0)
            continue;
        strcpy(filename[len++], file->d_name); //保存遍历到的文件名
        //判断该文件是否是目录，及是否已搜索了三层，这里我定义只搜索了三层目录.
        if (stat(file->d_name, &sb) >= 0 && S_ISDIR(sb.st_mode) && depth <= 3)
        {
            trave_dir(file->d_name, depth + 1);
        }
    }
    closedir(d);
    return 0;
}