/*
 * CCookies.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "CCookies.h"

CCookies::CCookies()
{
	m_cookies.clear();
	m_cookieid = 1;
}

CCookies::~CCookies()
{
	m_cookies.clear();
	m_cookieid = 1;
}

int CCookies::getCookies()
{
	//get from db
	CSingleCrawl *singlecrawl = CSingleCrawl::GetInstance();
	CDBServer dbcrawl = singlecrawl->m_db;
	string cookiessrc = "";
	vector<string>websites = dbcrawl.SelectMysql_cookies(m_cookieid);
	for(int websiteindex = 0; websiteindex < websites.size(); websiteindex++)
	{
		CCookie cookie;
		cookie.setWebsite(websites[websiteindex]);
		cookie.getCookie(m_cookieid);
		m_cookies.push_back(cookie);
	}
	return 0;
}

void CCookies::getCookies(vector<CCookie> &cookies)
{
	cookies = m_cookies;
}

void CCookies::setCookieId(int cookieid)
{
	m_cookieid = cookieid;
}

int CCookies::getCookieId()
{
	return m_cookieid;
}

