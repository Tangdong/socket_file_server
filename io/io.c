#include "io.h"

int location_filefd(int filefd, int pos)
{
    return lseek(filefd,pos ,SEEK_SET);
}

void show_read_date(char *buf,int len, int hex)
{
	if (hex)
	{
        printf("read data = [");
        for (int i = 0; i < len; i++)
        {
            printf("%02x", buf[i]);
        }
        printf("]\n");
	}
	else
	{
        printf("read data = [");
        for (int i = 0; i < len; i++)
        {
            printf("%c", buf[i]);
        }
        printf("]\n");
	}
}

void test_io()
{
	int fd = open("/root/study/socket/document/boot.txt", O_RDONLY);
	char buf[16] = { 0 };
	printf("fd = %d\n", fd);
	int ret = location_filefd(fd, 4);
	ret = read(fd, buf, 4);
	show_read_date(buf, 4, 0);
	while (1)
	{

	}
}