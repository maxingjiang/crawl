/*
 * singleCrawl.cpp
 *
 *  Created on: Aug 30, 2016
 *      Author: root
 */

#include "singleCrawl.h"

CSingleCrawl* CSingleCrawl::m_pInstance = NULL;
CDBServer CSingleCrawl::m_db;
CProxyManager CSingleCrawl::m_proxymanager;

CSingleCrawl::CSingleCrawl()
{
	string host = "127.0.0.1";
	string user = "root";
	string pass = "123456";
	string dbname = "crawldb";
	int poolSize = 10;

	m_db.initMysqlPool(host,user,pass,dbname,poolSize);

	m_proxymanager.getProxyFromDB(&m_db, 10);

}

CSingleCrawl::CSingleCrawl(const CSingleCrawl& crawl)
{
}

CSingleCrawl& CSingleCrawl::operator=(const CSingleCrawl& crawl)
{
	return *this;
}

CSingleCrawl::~CSingleCrawl()
{
	m_db.destroyMysqlPool();
}

CSingleCrawl* CSingleCrawl::GetInstance()
{
    if(m_pInstance == NULL)  //判断是否第一次调用
    {
        m_pInstance = new CSingleCrawl();
    }
    return m_pInstance;
}

void CSingleCrawl::ReleaseInstance()
{
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}
