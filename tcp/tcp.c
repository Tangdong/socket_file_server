#include "tcp.h"

/* 定义服务器初始化函数 */
int server_init(char* ip, short port)
{
    int ret;
    int listenfd;
    struct sockaddr_in srvaddr;
    int opt;

    /* 创建套接字文件 */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("server_init->socket");
        return -1;
    }
    printf("listenfd = %d\n", listenfd);

    /* 设置套接字lietenfd，允许地址和端口重用 */
    int op = 1;
    ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (void*)&op, sizeof(op));
    if (ret == -1) {
        perror("setsockopt");
        return -1;
    }

    /* 绑定服务器的ip地址和端口号 */
    memset(&srvaddr, 0, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(port);
    if (ip == NULL)
        srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    else
        srvaddr.sin_addr.s_addr = inet_addr(ip);
    ret = bind(listenfd, (const struct sockaddr*)&srvaddr, sizeof(srvaddr));
    if (ret == -1) {
        perror("server_init->bind");
        return -1;
    }
    printf("bind success\n");

    /* 启动监听 */
    ret = listen(listenfd, 1024);
    if (ret == -1) {
        perror("server_init->listen");
        return -1;
    }

    return listenfd;
}

/* 定义服务器等待客户端的连接请求，建立连接 */
int server_wait_client_connect(int listenfd)
{
    int connfd;
    socklen_t addrlen;
    struct sockaddr_in cltaddr;

    //accept(listenfd, NULL, NULL);
    addrlen = sizeof(cltaddr);
    connfd = accept(listenfd, (struct sockaddr*)&cltaddr, &addrlen);
    if (connfd == -1) {
        perror("accept");
        return -1;
    }
    //printf("IP : %s connet success connfd = %d\n", inet_ntoa(cltaddr.sin_addr), connfd);

    return connfd;
}