/*
 * updateBusLineAndProxy.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: root
 */

//包含zmq的头文件
#include "runSocket.h"
#include "runSocket1.h"

using namespace std;


int main(int argc, char * argv[])
{

	CgetDataFromUrl cr;
	cr.writebuslineToConf();
	exit(0);
}



