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

ProxyIP::ProxyIP(std::string filename)
{
	m_filename = filename;
}

ProxyIP::~ProxyIP()
{
	m_filename = "";
}

vector<ip_port> ProxyIP::readProxy()
{
	vector<ip_port> proxys;
    const int LINE_LENGTH = 1024;
    char str[LINE_LENGTH];
    crawl cr;
    ifstream fin(m_filename.c_str());
    while( fin.getline(str,LINE_LENGTH) != NULL)
    {
    	cr.clear();
    	std::vector<std::string> iplines = cr.split(str, ":");
        //std::cout << "proxy: " << iplines[0]<<":"<<iplines[1] << std::endl;
    	ip_port proxy;
    	proxy.ip = iplines[0];
    	proxy.port = atoi(iplines[1].c_str());
    	proxys.push_back(proxy);
    }
    return proxys;
}




