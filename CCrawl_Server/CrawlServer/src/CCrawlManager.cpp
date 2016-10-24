/*
 * CCrawlManager.cpp
 *
 *  Created on: Aug 1, 2016
 *      Author: root
 */

#include "CCrawlManager.h"


CCrawlManager::CCrawlManager()
{
	curl_global_init(CURL_GLOBAL_ALL);
	m_proxy = NULL;
	m_crawls.clear();
}

CCrawlManager::~CCrawlManager()
{
	curl_global_cleanup();
	CSingleCrawl *singlecrawl = CSingleCrawl::GetInstance();
	singlecrawl->ReleaseInstance();

	for(unsigned i = 0; i < m_crawls.size(); ++i)
	{
		delete m_crawls[i];
		m_crawls[i] = NULL;
	}
}

CCrawl* CCrawlManager::createCrawl()
{
	CCrawl *crawl = new CCrawl();
	m_crawls.push_back(crawl);
	return crawl;
}

int CCrawlManager::deleteCrawl(CCrawl *crawl)
{
	vector<CCrawl *>::iterator iter = m_crawls.begin();
	for( ; iter != m_crawls.end(); iter++)
	{
		if(crawl == *iter)
		{
			m_crawls.erase(iter++);
			break;
		}
	}
	delete crawl;
	return 0;
}


