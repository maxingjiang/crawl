/*
 * testurls.cpp
 *
 *  Created on: Jun 23, 2016
 *      Author: root
 */

#include "testurls.h"

#include "CCrawl.h"

void Ctesturl::testUrl()
{
	CCrawl body;
	const int LINE_LENGTH = 1024;
	char src[LINE_LENGTH+1];
    string str;
    int urlnum = 0;
    string filename = "./url.conf";
    FILE *fp = fopen(filename.c_str(), "r");
    if(!fp)
    {
        printf("error file %s \n", filename.c_str());
        return ;
    }
    while(1)
    {
    	// 加锁以判断文件是否已经被加锁了
    	if(flock(fileno(fp), LOCK_EX | LOCK_NB) == 0)
        {
    		//printf("file %s is unlock status \n", filename.c_str());
        	while ((fgets (src, LINE_LENGTH, fp)) != NULL)
            {
            	str = src;
            	size_t n = str.find_last_not_of(" \r\n\t");
                //std::cout << "src: "<< str << std::endl;
                if( n != string::npos )
                {
                	str.erase( n + 1 , str.size() - n );
                }
                //requestHeaders.push_back(str);
                cout<<urlnum<<"==>url: "<<str<<endl;
                body.GET_Html(str, "aaa.png");
        		urlnum++;
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
}

