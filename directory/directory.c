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
    DIR* d; //����һ�����
    struct dirent* file; //readdir�����ķ���ֵ�ʹ��������ṹ����
    struct stat sb;

    if (!(d = opendir(path)))
    {
        printf("error opendir %s!!!/n", path);
        return -1;
    }
    while ((file = readdir(d)) != NULL)
    {
        //�ѵ�ǰĿ¼.����һ��Ŀ¼..�������ļ���ȥ����������ѭ������Ŀ¼
        if (strncmp(file->d_name, ".", 1) == 0)
            continue;
        strcpy(filename[len++], file->d_name); //������������ļ���
        //�жϸ��ļ��Ƿ���Ŀ¼�����Ƿ������������㣬�����Ҷ���ֻ����������Ŀ¼.
        if (stat(file->d_name, &sb) >= 0 && S_ISDIR(sb.st_mode) && depth <= 3)
        {
            trave_dir(file->d_name, depth + 1);
        }
    }
    closedir(d);
    return 0;
}