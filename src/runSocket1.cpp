/*
 * runSocket1.cpp
 *
 *  Created on: May 30, 2016
 *      Author: root
 */
#include "runSocket1.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#define MYPORT  7766
#define QUEUE   20
#define BUFFER_SIZE 1024

int CrunSocket1::init(const char * port)
{
    m_server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
    ClogCPP log;
    log.init();
    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(MYPORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("bind:");
    ///bind，成功返回0，出错返回-1
    if(bind(m_server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }

    LOG4CPLUS_DEBUG(ClogCPP::m_logger, "listen debug logging....");
    ///listen，成功返回0，出错返回-1
    if(listen(m_server_sockfd,QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }
    curl_global_init(CURL_GLOBAL_ALL);
    m_thread_pool = new Cthreadpool(10);
    Cbusinfo bus;
    m_cbuslist = new CBusLists();
    m_cbuslist->m_threadargss = bus.getArgsForThread();
    m_poolbuslist = new CpoolBuslist();
    m_poolbuslist->m_thread_pool = m_thread_pool;
    m_poolbuslist->m_cbuslist = m_cbuslist;
    return 1;
}

int CrunSocket1::destroy()
{
	delete m_thread_pool;
	delete m_cbuslist;
	delete m_poolbuslist;
	return 0;
}

int CrunSocket1::run()
{
    ///客户端套接字
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    while(1)
    {
    	   int conn = accept(m_server_sockfd, (struct sockaddr*)&client_addr, &length);
    	    if(conn<0)
    	    {
    	        perror("connect");
    	        exit(1);
    	    }

    	    while(1)
    	    {
    	        LOG4CPLUS_DEBUG(ClogCPP::m_logger, "run begin======>");
    	        Cbusinfo bs;
    	        bs.runPthread(m_poolbuslist);
    	        string jsonsrc = bs.mergeSrcs(m_poolbuslist->m_cbuslist->m_buslist);
    	       // string jsonsrc = "hello";
    	        if(jsonsrc.length() <= 0)
    	            jsonsrc = "heartbeat";
    	        cout<<"begin send data=====>\n";
    	        int recv = send(conn, (char*)jsonsrc.c_str(), jsonsrc.length(),0);
    	        cout<<"recv: "<<recv<<endl;
    	    }
    	    close(conn);
    	    close(m_server_sockfd);
    }

    curl_global_cleanup();
	if(m_thread_pool->pool->cur_queue_size == 0)
	{
		cout<<"===========exit\n";
		m_thread_pool->pool_destroy ();
	}
    return 0;
}

