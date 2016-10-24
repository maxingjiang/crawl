/*
 * Proxy.h
 *
 *  Created on: May 19, 2016
 *      Author: root
 */

#ifndef INCLUDE_Proxy_H_
#define INCLUDE_Proxy_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <curl/curl.h>
#include <curl/easy.h>
#include "CHttpRequest.h"

using namespace std;

class Cip_port
{
public:
	string m_ip;
	int m_port;
};

class CProxy
{
public:
	CProxy();
	~CProxy();

	void setProxy(const string &ip, int port);
	Cip_port getProxy();
	void sendProxy(CHttpRequest * httpRequest);
	/*
	vector<Cip_port> readProxy(string filename);
	vector<Cip_port> getUsefulProxyIP(vector<Cip_port> proxyips);
	int testProxyip(string ip, int port);
	void getAllUsefulProxyIP();
	*/
private:
	Cip_port m_proxy;

};

#endif /* INCLUDE_Proxy_H_ */
