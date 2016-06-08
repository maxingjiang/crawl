/*
 * getProxy.cpp
 *
 *  Created on: May 19, 2016
 *      Author: root
 */

#include <iostream>
#include "getProxy.h"
#include "crawl.h"
#include <sys/file.h>

using namespace std;

vector<Cip_port> CProxyIP::readProxy(string filename)
{
	vector<Cip_port> proxys;
    const int LINE_LENGTH = 1024;
    char src[LINE_LENGTH+1];
    Ccrawl cr;
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
    			int n = str.find_last_not_of(" \r\n\t");
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




