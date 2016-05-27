//包含zmq的头文件 
#include <zmq.h>
#include "stdio.h"
#include <iostream>
#include <string>
#include "threadpool.h"
#include "readrequest.h"
#include "crawl.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include "getProxy.h"
#include "businfo.h"
#include "getDataFromUrl.h"
#include "common.h"
#include <pthread.h>

using namespace std;


int main(int argc, char * argv[])
{
	void * pCtx = NULL;
	void * pSock = NULL;
    const char * pAddr = "tcp://*:7766";
    logCPP::info(__FILE__, __LINE__, "log==========");
    //创建context，zmq的socket 需要在context上进行创建 
    if((pCtx = zmq_ctx_new()) == NULL)
    {
        return 0;
    }
    //创建zmq socket ，socket目前有6中属性 ，这里使用dealer方式
    //具体使用方式请参考zmq官方文档（zmq手册） 
    if((pSock = zmq_socket(pCtx, ZMQ_DEALER)) == NULL)
    {
        zmq_ctx_destroy(pCtx);
        return 0;
    }
    logCPP::error(__FILE__, __LINE__, "error");
    int iRcvTimeout = 5000;// millsecond
    //设置zmq的接收超时时间为5秒 
    if(zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &iRcvTimeout, sizeof(iRcvTimeout)) < 0)
    {
        zmq_close(pSock);
        zmq_ctx_destroy(pCtx);
        return 0;
    }
    //绑定地址 tcp://*:7766 
    //也就是使用tcp协议进行通信，使用网络端口 7766
    if(zmq_bind(pSock, pAddr) < 0)
    {
        zmq_close(pSock);
        zmq_ctx_destroy(pCtx);
        return 0;
    }
    curl_global_init(CURL_GLOBAL_ALL);
    printf("bind at : %s\n", pAddr);
    businfo bus;
    busLists::threadargss = bus.getArgsForThread();
    threadpool::pool_init (10);

    while(1)
    {
        printf("waitting...\n");

        businfo bs;
        bs.runPthread();
        string jsonsrc = bs.mergeJsonSrcs(busLists::buslist);
        cout<<"begin send data=====>\n";
        if(zmq_send(pSock, jsonsrc.c_str(), jsonsrc.length(), 0) < 0)
        {
        	printf("send message error\n");
        }
        printf("send message succeed\n");
        printf("sleep 5s.....\n");
        sleep(5);
    }

    curl_global_cleanup();
	if(threadpool::pool->cur_queue_size == 0)
	{
		cout<<"===========exit\n";
		threadpool::pool_destroy ();
	}

    return 0;
}
