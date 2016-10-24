/*
 * SocketServer.h
 *
 *  Created on: May 30, 2016
 *      Author: root
 */

#ifndef INCLUDE_RUNSOCKET_H_
#define INCLUDE_RUNSOCKET_H_

#include "zeromq/zmq.h"
#include "stdio.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>

using namespace std;

class CSocketServer
{
public:
	int init(const char * port);
	int run(const string &jsonsrc);
	int destroy();
private:
	void * m_pCtx;
	void * m_pSock;
	int m_rc;
    const char * m_port;

};

#endif /* INCLUDE_RUNSOCKET_H_ */
