/*
 * Proxy.cpp
 *
 *  Created on: May 19, 2016
 *      Author: root
 */

#include <iostream>
#include "Proxy.h"
#include <sys/file.h>
#include "common.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include "split.h"

CProxy::CProxy()
{
	m_proxy.m_ip.clear();
	m_proxy.m_port = 0;
}

CProxy::~CProxy()
{
	m_proxy.m_ip.clear();
	m_proxy.m_port = 0;
}

void CProxy::setProxy(const string &ip, int port)
{
	m_proxy.m_ip = ip;
	m_proxy.m_port = port;
}

Cip_port CProxy::getProxy()
{
	return m_proxy;
}

void CProxy::sendProxy(CHttpRequest * httpRequest)
{
	if(m_proxy.m_ip.size() > 0 && m_proxy.m_port > 0)
	{
		cout<<__FILE__<<__LINE__<<"ip: "<<m_proxy.m_ip<<",port: "<<m_proxy.m_port<<endl;
		curl_easy_setopt(httpRequest->m_curl, CURLOPT_PROXY, m_proxy.m_ip.c_str());
		curl_easy_setopt(httpRequest->m_curl, CURLOPT_PROXYPORT, m_proxy.m_port);
	}
}

/*
vector<Cip_port> CProxy::readProxy(string filename)
{
	vector<Cip_port> proxys;
    const int LINE_LENGTH = 1024;
    char src[LINE_LENGTH+1];
    Csplit cr;
    string str;
    FILE *fp = fopen(filename.c_str(), "r");
    if(!fp)
    {
        printf("error file %s \n", filename.c_str());
        return proxys;
    }
    while(1)
	{
        // 加锁以判断文件是否已经被加锁了
		if(flock(fileno(fp), LOCK_EX | LOCK_NB) == 0)
		{
			printf("file %s is unlock status \n", filename.c_str());
    		while ((fgets (src, LINE_LENGTH, fp)) != NULL)
			{
    			str = src;
    			unsigned int n = str.find_last_not_of(" \r\n\t");
    			//std::cout << "src: "<< str << std::endl;
    			if( n != string::npos )
    			{
    			    str.erase( n + 1 , str.size() - n );
    			}
    	    	std::vector<std::string> iplines = cr.split(src, ":");
    	    	if(iplines.size() == 2)
    	    	{
    	    		//std::cout << "proxy: " << iplines[0]<<":"<<iplines[1] << std::endl;
    	    		Cip_port proxy;
    	    		proxy.m_ip = iplines[0];
    	    		proxy.m_port = atoi(iplines[1].c_str());
    	    		proxys.push_back(proxy);
    	    	}
			}
			fclose(fp);
			flock(fileno(fp), LOCK_UN);
			break;
		}
		else
		{
			printf("file %s is locked, please wait \n", filename.c_str());
			sleep(1);
		}
	}

    return proxys;
}

vector<Cip_port> CProxy::getUsefulProxyIP(vector<Cip_port> proxyips)
{
	vector<Cip_port> proxys;
	vector<Cip_port>::iterator iter = proxyips.begin();
	char cmdsrc[] = "echo > proxy.txt";
	system(cmdsrc);
    for(; iter != proxyips.end(); iter++)
    {
    	int num = testProxyip(iter->m_ip, iter->m_port);
    	if(num == 1)
    	{
    		Cip_port proxy;
    		proxy.m_ip = iter->m_ip;
    		proxy.m_port = iter->m_port;
    		proxys.push_back(proxy);
    		char portsrc[10] = {0x0};
    		sprintf(portsrc, "%d", iter->m_port);
    		string cmd = "echo "+iter->m_ip+":"+string(portsrc)+" >> "+PROXYCONF;
    		system(cmd.c_str());
    	}
    	//sleep(1);
    }
    return proxys;
}

int CProxy::testProxyip(string ip, int port)
{
    CURL *curl;
    //CURLcode res;
    curl = curl_easy_init();
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_POST, 1L);
    	curl_easy_setopt(curl, CURLOPT_PROXY, ip.c_str());
    	curl_easy_setopt(curl, CURLOPT_PROXYPORT, port);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1L);
        //curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        //curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, "http://222.85.139.244:1001/BusService/Require_AllRouteData/?TimeStamp=1");
        string buffer_data;
        buffer_data.clear();
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Csplit::write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer_data);
        string buffer_header;
        buffer_header.clear();
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, Csplit::write_header);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &buffer_header);
        curl_easy_perform(curl);
        //std::cout<<"buffer_data length===>\n"<<strlen(buffer_data)<<std::endl;
        curl_easy_cleanup(curl);
        //curl_slist_free_all(headers);
        int num = string(buffer_header).find("200 OK");
        std::cout<<ip<<":"<<port<<" num:"<<num<<std::endl;
        if( num >= 0)
        {
        	cout<<"<<======pass=========>>"<<ip<<":"<<port<<endl;
        	return 1;
        }
        else
        	return 0;
    }
    return 0;
}

void CProxy::getAllUsefulProxyIP()
{
	vector<Cip_port> ips = readProxy(TESTPROXY);
	getUsefulProxyIP(ips);
}
*/

