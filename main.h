/*
* 
* 协议: 用 | 隔开
* 
* client
* 例如  0|1.txt|11
* 0：当前状态
* 1.txt：文件名
* 11：当前文件字节
* 
* server
* 
* 下次状态
* 
* 
* get 1.txt
* 
*    client                            server
* send(0,filename,size)             requese(yes/no,)
* 
*/