#include <iostream>
#include "stdio.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include "SocketServer.h"

using namespace std;

int main(int argc, char * argv[])
{
    void * pCtx = NULL;
    void * pSock = NULL;
    //使用tcp协议进行通信，需要连接的目标机器IP地址为192.168.1.2
    //通信使用的网络端口 为7766
    const char * pAddr = "tcp://127.0.0.1:7767";

    //创建context
    if((pCtx = zmq_ctx_new()) == NULL)
    {
        return 0;
    }
    //创建socket
    if((pSock = zmq_socket(pCtx, ZMQ_SUB)) == NULL)
    {
        zmq_ctx_destroy(pCtx);
        return 0;
    }
    int iSndTimeout = 60000;// millsecond
    //设置过滤器，不然接收不到数据
    zmq_setsockopt (pSock, ZMQ_SUBSCRIBE, "", 0);
    //设置接收超时
    if(zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &iSndTimeout, sizeof(iSndTimeout)) < 0)
    {
        zmq_close(pSock);
        zmq_ctx_destroy(pCtx);
        return 0;
    }
    //连接目标IP127.0.0.1，端口8023
    if(zmq_connect(pSock, pAddr) < 0)
    {
        zmq_close(pSock);
        zmq_ctx_destroy(pCtx);
        return 0;
    }
    char *szMsg = new char[3000000];
    //循环发送消息
    while(1)
    {
		memset(szMsg, 0 , 3000000);
		printf("begin to recv...\n");
        if(zmq_recv(pSock, szMsg, 3000000, 0) < 0)
        {
            printf("error = %s\n", zmq_strerror(errno));
	    	continue;
        }
        printf("recv message  succeed\n");
        printf("memset message : [%s] succeed\n", szMsg);
    }
    delete szMsg;
    return 0;
}
