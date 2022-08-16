#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include "./tcp/tcp.h"
#include "./directory/directory.h"
#include "./io/io.h"

#define EXAMINEFILE 0   /* �����ļ��Ƿ�����ڷ������� */
#define GOONFILE    1   /*���������ļ�*/
#define GETFILE     2   /*�����ļ�*/
typedef struct 
{
    int size;
    char filename[24];
}file_t;

char(*filename)[][256] = NULL;
int file_count = 0;

int executeShell(char* result, char* shell)
{
    FILE * stream = (FILE*)popen(shell, "r");
    char   buf[512] = {0};
    memset(buf, 0, sizeof(buf));
    if (NULL == stream)
    {
        printf("error\n");
    }
    else
    {
        printf("OK\n");
    }
    // ret = ferror(stream);
    int ret = fread(buf, sizeof(char), sizeof(buf), stream);
    memcpy(result, buf, ret);
    return ret;
}

int getCatalogFiles(char *filenames,char *catalog)
{
    char shell[32] = { 0 };
    int count = 0;
    int pos = 0;

    char buf[128] = { 0 };
    sprintf(shell, "ls %s", catalog);
    int ret = executeShell(buf, shell);
    for (int i = 0; i < ret; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '|';
        }
    }
    buf[strlen(buf) - 1] = '\0';
    printf("buf : %s\n", buf);
    memcpy(filenames, buf, strlen(buf));
    return 0;
}

int main()
{
    int ret;
    int listenfd;
    int connfd;
    char buf[256];
    file_t file = {0};
    /* 1. �������ĳ�ʼ�� */
    listenfd = server_init("127.0.0.1", 8888);
    //listenfd = server_init(NULL, 8888);
    if (listenfd == -1)
        exit(EXIT_FAILURE);
    printf("server init success\n");

    //getCatalogFiles(filenames, "/root/study/socket/document");

    ret = get_dir_files("/root/study/socket/document",0, &filename,&file_count);
    if (0 != ret)
    {
        printf("get_dir_files  error\n");
    }
    for (int i = 0; i < file_count; i++)
    {
        printf("%s \t", (*filename)[i]);
    }
    puts("");
    /* 2. �������ȴ��ͻ��˵��������󣬽������� */
    connfd = server_wait_client_connect(listenfd);
    printf("client in\n");
    if (connfd == -1)
        exit(EXIT_FAILURE);
    char ch;
    char* p = NULL;
    /* 3. ����������ͻ��˵��������󣬲��������ݣ����������� */
    while (1) {// filenames
        memset(buf, 0, sizeof(buf));
        ret = read(connfd, buf, sizeof(buf));
        if (0 == ret)
        {
            break;
        }
        ch = buf[0] - '0';
        switch (ch)
        {
        case EXAMINEFILE:
            p = strstr(buf+2,"|");
            memcpy(file.filename, buf + 2, p - buf - 2);
            file.size = atoi(p + 1);
            printf("file.filename = %s\n", file.filename);
            break;
        case GOONFILE:
            break;
        case GETFILE:
            break;
        default:
            break;
        }
        printf("buf : %s\n", buf);
        write(connfd, buf, ret);
    }

    return 0;
}