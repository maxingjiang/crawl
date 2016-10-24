/*
 * CCrawlManager.h
 *
 *  Created on: Aug 1, 2016
 *      Author: root
 */

#ifndef CRAWLSERVER_INCLUDE_CCRAWLMANAGER_H_
#define CRAWLSERVER_INCLUDE_CCRAWLMANAGER_H_

#include "CCrawl.h"
#include "CProxyManager.h"
#include "singleCrawl.h"

class CCrawlManager
{
public:
	CCrawlManager();
	virtual ~CCrawlManager();
	CCrawl* createCrawl();
	int deleteCrawl(CCrawl *crawl);


private:
	vector<CCrawl*>m_crawls;
	CProxyManager *m_proxy;
};

#endif /* CRAWLSERVER_INCLUDE_CCRAWLMANAGER_H_ */
