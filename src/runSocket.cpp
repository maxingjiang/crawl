/*
 * runSocket.cpp
 *
 *  Created on: May 30, 2016
 *      Author: root
 */
#include "runSocket.h"


int CrunSocket::init(const char * port)
{
	m_pCtx = NULL;
	m_pSock = NULL;
    m_pAddr = port;
    //创建context，zmq的socket 需要在context上进行创建
    if((m_pCtx = zmq_ctx_new()) == NULL)
    {
        return 0;
    }
    ClogCPP log;
    log.init();
    LOG4CPLUS_INFO(ClogCPP::m_logger, "begin logging....");
    LOG4CPLUS_DEBUG(ClogCPP::m_logger, "begin debug logging....");
    //exit(0);
    //创建zmq socket ，socket目前有6中属性 ，这里使用dealer方式
    //具体使用方式请参考zmq官方文档（zmq手册）
    if((m_pSock = zmq_socket(m_pCtx, ZMQ_DEALER)) == NULL)
    {
        zmq_ctx_destroy(m_pCtx);
        return 0;
    }
    int iRcvTimeout = 5000;// millsecond
    //设置zmq的接收超时时间为5秒
    if(zmq_setsockopt(m_pSock, ZMQ_RCVTIMEO, &iRcvTimeout, sizeof(iRcvTimeout)) < 0)
    {
        zmq_close(m_pSock);
        zmq_ctx_destroy(m_pCtx);
        return 0;
    }
    //绑定地址 tcp://*:port
    //也就是使用tcp协议进行通信，使用网络端口 port
    if(zmq_bind(m_pSock, m_pAddr) < 0)
    {
        zmq_close(m_pSock);
        zmq_ctx_destroy(m_pCtx);
        return 0;
    }
    curl_global_init(CURL_GLOBAL_ALL);
    printf("bind at : %s\n", m_pAddr);
    m_thread_pool = new Cthreadpool(10);
    Cbusinfo bus;
    m_cbuslist = new CBusLists();
    m_cbuslist->m_threadargss = bus.getArgsForThread();
    m_poolbuslist = new CpoolBuslist();
    m_poolbuslist->m_thread_pool = m_thread_pool;
    m_poolbuslist->m_cbuslist = m_cbuslist;
    return 1;
}

int CrunSocket::destroy()
{
	delete m_thread_pool;
	delete m_cbuslist;
	delete m_poolbuslist;
	return 0;
}

int CrunSocket::run()
{
    while(1)
    {
        printf("waitting...\n");

        Cbusinfo bs;
        bs.runPthread(m_poolbuslist);
        string jsonsrc = bs.mergeJsonSrcs(m_poolbuslist->m_cbuslist->m_buslist);
        cout<<"begin send data=====>\n";
        while(zmq_send(m_pSock, jsonsrc.c_str(), jsonsrc.length(), 0) < 0)
        {
        	printf("send message error\n");
        	sleep(2);
        	continue;
        }
        printf("send message succeed\n");
        printf("sleep 5s.....\n");
        sleep(5);
    }

    curl_global_cleanup();
	if(m_thread_pool->pool->cur_queue_size == 0)
	{
		cout<<"===========exit\n";
		m_thread_pool->pool_destroy ();
	}

    return 0;
}

