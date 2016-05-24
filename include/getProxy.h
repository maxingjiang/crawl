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

struct ip_port
{
	string ip;
	int port;
};

class ProxyIP
{
	public:
		ProxyIP(std::string filename);
		~ProxyIP();
		vector<ip_port> readProxy();
	public:
		string m_filename;
};



#endif /* INCLUDE_GETPROXY_H_ */
