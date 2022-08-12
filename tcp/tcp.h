#ifndef __TCP_H__
#define __TCP_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <sys/time.h>
#include <unistd.h>

int server_init(char* ip, short port);

int server_wait_client_connect(int listenfd);
#endif // !__TCP_H__
