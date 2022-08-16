#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int location_filefd(int filefd, int pos);

void show_read_date(char* buf,int len,int hex);

void test_io();