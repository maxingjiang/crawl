/*
 * runSocket.cpp
 *
 *  Created on: May 30, 2016
 *      Author: root
 */

#include "SocketServer.h"

int CSocketServer::init(const char * port)
{
    m_pCtx = NULL;
    m_pSock = NULL;
    m_port = port;
    //创建context，zmq的socket 需要在context上进行创建
    if((m_pCtx = zmq_ctx_new()) == NULL)
    {
        return 0;
    }
    //创建zmq socket ，socket目前有6中属性 ，这里使用pub方式
    //具体使用方式请参考zmq官方文档（zmq手册）
    if((m_pSock = zmq_socket(m_pCtx, ZMQ_PUB)) == NULL)
    {
    	printf("zmq_socket faild....\n");
        zmq_ctx_destroy(m_pCtx);
        return 0;
    }
    int iRcvTimeout = 5000;// millsecond
    //设置zmq的接收超时时间为5秒
    if(zmq_setsockopt(m_pSock, ZMQ_RCVTIMEO, &iRcvTimeout, sizeof(iRcvTimeout)) < 0)
    {
    	printf("zmq_setsockopt faild....\n");
        zmq_close(m_pSock);
        zmq_ctx_destroy(m_pCtx);
        return 0;
    }
    //绑定地址 tcp://*:port
    //也就是使用tcp协议进行通信，使用网络端口 port

    m_rc = zmq_bind(m_pSock, m_port);
    if(m_rc < 0)
    {
    	printf("zmq_bind faild....\n");
        zmq_close(m_pSock);
        zmq_ctx_destroy(m_pCtx);
        return 0;
    }

    printf("bind at : %s\n",m_port);

    return 1;
}

int CSocketServer::destroy()
{
    zmq_close(m_pSock);
    zmq_ctx_destroy(m_pCtx);
	return 0;
}

int CSocketServer::run(const string &jsonsrc)
{
    unsigned int rc = 0;

    while(1)
    {
    	rc = 0;
        cout<<"begin send data=====>"<<jsonsrc.length()<<endl;
        rc = zmq_send(m_pSock, jsonsrc.c_str(), jsonsrc.length(), 0);
        assert(rc == jsonsrc.length());
        cout<<"send message succeed\n";
        cout<<"sleep 1s.....\n";
        sleep(1);
    }

    return 0;
}

