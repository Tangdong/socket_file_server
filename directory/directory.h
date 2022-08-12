#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__
#include <stdio.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>
int get_dir_files(char* path, int depth, char (**file)[][256], int *count);


int trave_dir(char* path, int depth);

#endif // __DIRECTORY_H__
