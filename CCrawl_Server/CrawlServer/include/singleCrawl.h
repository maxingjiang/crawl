/*
 * singleCrawl.h
 *
 *  Created on: Aug 30, 2016
 *      Author: root
 */

#ifndef CRAWLSERVER_INCLUDE_SINGLECRAWL_H_
#define CRAWLSERVER_INCLUDE_SINGLECRAWL_H_

#include <iostream>
#include "CProxyManager.h"
#include "CDBServer.h"

using namespace std;

class CSingleCrawl
{
private:
	CSingleCrawl();   //构造函数是私有的
	~CSingleCrawl();
	CSingleCrawl(const CSingleCrawl& crawl);
	CSingleCrawl& operator=(const CSingleCrawl& crawl);

    static CSingleCrawl *m_pInstance;
    /*
    class CDeleteSingleCrawl // 它的唯一工作就是在析构函数中删除CSingleCrawl的实例
    {
    public:
        ~CDeleteSingleCrawl()
        {
            if (CSingleCrawl::m_pInstance)
            {
                delete CSingleCrawl::m_pInstance;
            }
        }
    };
    static CDeleteSingleCrawl delsinglecrawl; // 定义一个静态成员，在程序结束时，系统会调用它的析构函数
	*/
public:
    static CSingleCrawl * GetInstance();
    static void ReleaseInstance();
    static CDBServer m_db;
    static CProxyManager m_proxymanager;

};

#endif /* CRAWLSERVER_INCLUDE_SINGLECRAWL_H_ */
