/*
 * getProxy.h
 *
 *  Created on: May 19, 2016
 *      Author: root
 */

#ifndef INCLUDE_GETPROXY_H_
#define INCLUDE_GETPROXY_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Cip_port
{
public:
	string m_ip;
	int m_port;
};

class CProxyIP
{
	public:
		vector<Cip_port> readProxy(string filename);

};



#endif /* INCLUDE_GETPROXY_H_ */
