/*
 * runSocket.h
 *
 *  Created on: May 30, 2016
 *      Author: root
 */

#ifndef INCLUDE_RUNSOCKET_H_
#define INCLUDE_RUNSOCKET_H_

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

class CrunSocket
{
public:
	int init(const char * port);
	int run();
	int destroy();
private:
	void * m_pCtx;
	void * m_pSock;
    const char * m_pAddr;
    Cthreadpool *m_thread_pool;
    CBusLists *m_cbuslist;
    CpoolBuslist *m_poolbuslist;
};


#endif /* INCLUDE_RUNSOCKET_H_ */
