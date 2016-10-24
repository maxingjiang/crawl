/*
 * CCookieManager.cpp
 *
 *  Created on: Aug 12, 2016
 *      Author: root
 */

#include "CCookieManager.h"
#include "singleCrawl.h"

CCookieManager::CCookieManager()
{
	m_cookiesMgr.clear();
}

CCookieManager::~CCookieManager()
{
	m_cookiesMgr.clear();
}

int CCookieManager::getCookiesMgr()
{
	//get from db
	CSingleCrawl *singlecrawl = CSingleCrawl::GetInstance();
	CDBServer dbcrawl = singlecrawl->m_db;
	string cookiessrc = "";
	vector<string>cookiemgrs = dbcrawl.SelectMysql_cookies();
	for(int cookiemgrindex = 0;  cookiemgrindex < cookiemgrs.size(); cookiemgrindex++)
	{
		CCookies cookies;
		cookies.setCookieId(atoi(cookiemgrs[cookiemgrindex].c_str()));
		cookies.getCookies();
		m_cookiesMgr.push_back(cookies);
	}
	return 1;
}

void CCookieManager::getCookiesMgr(vector<CCookies> &cookiesMgr)
{
	cookiesMgr = m_cookiesMgr;
}

