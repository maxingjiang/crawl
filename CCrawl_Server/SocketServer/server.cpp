/*
 * main.cpp
 *
 *  Created on: Sep 13, 2016
 *      Author: root
 */

#include <iostream>

#include "SocketServer.h"

using namespace std;

int main()
{
	CSocketServer server;
	int status = server.init("tcp://*:7767");
	if(status == 0)
		return 0;
	while(1)
	{
		server.run("hello zmq");
		sleep(1);
	}
	server.destroy();

	return 0;
}


