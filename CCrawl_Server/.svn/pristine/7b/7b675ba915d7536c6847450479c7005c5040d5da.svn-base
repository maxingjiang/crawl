#include "../include/zeromq/zmq.h"
#include "stdio.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char * argv[])
{
    void * pCtx = NULL;
    void * pSock = NULL;
    //使用tcp协议进行通信，需要连接的目标机器IP地址为192.168.1.2
    //通信使用的网络端口 为7766 
    const char * pAddr = "tcp://127.0.0.1:7766";

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
    //连接目标IP192.168.1.2，端口7766 
    if(zmq_connect(pSock, pAddr) < 0)
    {
        zmq_close(pSock);
        zmq_ctx_destroy(pCtx);
        return 0;
    }
    //循环发送消息 
    while(1)
    {
        char *szMsg = new char[3000000];
        memset(szMsg, 0 , 3000000);
        /*
        char sendsrc[] = "get";
        printf("Enter to send...\n");
        if(zmq_send(pSock, sendsrc, sizeof(sendsrc), 0) < 0)
        {
            fprintf(stderr, "send message faild\n");
            continue;
        }
        printf("send message : [%s] succeed\n", szMsg);
        */
		while(1)
		{
			printf("begin to recv...\n");
        	if(zmq_recv(pSock, szMsg, 3000000, 0) < 0)
        	{
            	printf("error = %s\n", zmq_strerror(errno));
	    		continue;
        	}
        	printf("recv message : [***%s***] succeed\n", szMsg);
            FILE *pcookie;
            if ((pcookie = fopen("./a.txt", "w")) == NULL)
                return 0;
            fprintf(pcookie, "%s\n",szMsg);
            printf("save message succeed\n");
            fclose(pcookie);
            //sleep(20);
        	memset(szMsg, 0 , 3000000);
        	//printf("memset message : [%s] succeed\n", szMsg);
		}
		printf("recv message end===>\n");
        getchar();
    }

    return 0;
}
