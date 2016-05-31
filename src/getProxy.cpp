/*
 * getProxy.cpp
 *
 *  Created on: May 19, 2016
 *      Author: root
 */

#include <iostream>
#include "getProxy.h"
#include "crawl.h"

using namespace std;

vector<Cip_port> CProxyIP::readProxy(string filename)
{
	vector<Cip_port> proxys;
    const int LINE_LENGTH = 1024;
    char str[LINE_LENGTH];
    Ccrawl cr;
    ifstream fin(filename.c_str());
    while( fin.getline(str,LINE_LENGTH) != NULL)
    {
    	std::vector<std::string> iplines = cr.split(str, ":");
        //std::cout << "proxy: " << iplines[0]<<":"<<iplines[1] << std::endl;
    	Cip_port proxy;
    	proxy.m_ip = iplines[0];
    	proxy.m_port = atoi(iplines[1].c_str());
    	proxys.push_back(proxy);
    }
    return proxys;
}




