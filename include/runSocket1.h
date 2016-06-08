/*
 * runSocket1.h
 *
 *  Created on: Jun 2, 2016
 *      Author: root
 */

#ifndef INCLUDE_RUNSOCKET1_H_
#define INCLUDE_RUNSOCKET1_H_

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

class CrunSocket1
{
public:
	int init(const char * port);
	int run();
	int destroy();
private:
	int m_server_sockfd;
    Cthreadpool *m_thread_pool;
    CBusLists *m_cbuslist;
    CpoolBuslist *m_poolbuslist;
};



#endif /* INCLUDE_RUNSOCKET1_H_ */
