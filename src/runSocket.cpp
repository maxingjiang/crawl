/*
 * runSocket.cpp
 *
 *  Created on: May 30, 2016
 *      Author: root
 */
#include "runSocket.h"

extern pthread_mutex_t BACK_COMM_mutex;

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
    //exit(0);
    //创建zmq socket ，socket目前有6中属性 ，这里使用pub方式
    //具体使用方式请参考zmq官方文档（zmq手册）
    if((m_pSock = zmq_socket(m_pCtx, ZMQ_PUB)) == NULL)
    {
    	LOG4CPLUS_ERROR(ClogCPP::m_logger, "zmq_socket logging....");
        zmq_ctx_destroy(m_pCtx);
        return 0;
    }
    int iRcvTimeout = 5000;// millsecond
    //设置zmq的接收超时时间为5秒
    if(zmq_setsockopt(m_pSock, ZMQ_RCVTIMEO, &iRcvTimeout, sizeof(iRcvTimeout)) < 0)
    {
    	LOG4CPLUS_ERROR(ClogCPP::m_logger, "zmq_setsockopt logging....");
        zmq_close(m_pSock);
        zmq_ctx_destroy(m_pCtx);
        return 0;
    }
    //绑定地址 tcp://*:port
    //也就是使用tcp协议进行通信，使用网络端口 port

    m_rc = zmq_bind(m_pSock, m_pAddr);
    if(m_rc < 0)
    {
    	LOG4CPLUS_ERROR(ClogCPP::m_logger, "zmq_bind logging....");
        zmq_close(m_pSock);
        zmq_ctx_destroy(m_pCtx);
        return 0;
    }

    curl_global_init(CURL_GLOBAL_ALL);
    cout<<"bind at : "<<m_pAddr<<endl;
    m_thread_pool = new Cthreadpool(20);
    m_cbuslist = new CBusLists();
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
	Cbusinfo bus;
	string jsonsrc;
	vector<CBusPositionInfo> oldbuslist;
	vector<CBusPositionInfo> newbuslist;
    while(1)
    {
        newbuslist.clear();
        m_cbuslist->m_threadargss = bus.getArgsForThread();
        bus.runPthread(m_poolbuslist);

    	if(pthread_mutex_lock(&BACK_COMM_mutex)!=0)
    	{
            printf("buslist pthread_mutex_lock err !!\n");
            return 0;
    	}
        newbuslist = bus.checkNewBusList(oldbuslist, m_poolbuslist->m_cbuslist->m_buslist);
        oldbuslist.clear();
        bus.copyBusList(oldbuslist, m_poolbuslist->m_cbuslist->m_buslist);
    	if(pthread_mutex_unlock(&BACK_COMM_mutex)!=0) //unlock
        {
    		printf("buslist pthread_mutex_unlock err !!\n");
    		return 0;
        }

        jsonsrc = bus.mergeSrcslist(newbuslist);
        //string jsonsrc = "hello";
        if(jsonsrc.length() <= 0)
        {
        	printf("send message error\n");
            jsonsrc = "heartbeat";
        }
        cout<<"begin send data=====>\n";
        while(zmq_send(m_pSock, jsonsrc.c_str(), jsonsrc.length(), 0) < 0)
        {
        	cout<<"send message error\n";
        	sleep(2);
        	continue;
        }
        cout<<"send message succeed\n";
        cout<<"sleep 1s.....\n";
        sleep(1);
    }

    curl_global_cleanup();
	if(m_thread_pool->pool->cur_queue_size == 0)
	{
		cout<<"exit======>\n";
		m_thread_pool->pool_destroy ();
	}

    return 0;
}

