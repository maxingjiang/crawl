/*
 * CCookie.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "CCookie.h"

CCookie::CCookie()
{
	m_cookie.clear();
	m_website.clear();
	m_cookiesrc.clear();
}

CCookie::~CCookie()
{
	m_cookie.clear();
	m_website.clear();
	m_cookiesrc.clear();
}

int CCookie::saveCookie(int cookieid)
{
	//insert to db
	CSingleCrawl *singlecrawl = CSingleCrawl::GetInstance();
	CDBServer dbcrawl = singlecrawl->m_db;

    time_t curTime = time(NULL);
    tm * gmTime = gmtime(&curTime);
    char strTimeBuf[50];
    strftime(strTimeBuf, 100, " %a, %d %b %Y %X GMT;", gmTime);

	string cookieKey = "";
	string cookieValue = "";
	string domain = "";
	string path = "/";
	string sendUseage = "all";
	int isHttpOnly = 0;
	string created = strTimeBuf;
	string deadline = "this connection";

	for(int unitindex = 0; unitindex != m_cookie.size(); unitindex++)
	{
		cookieKey = m_cookie[unitindex].m_cookieKey;
		cookieValue = m_cookie[unitindex].m_cookieValue;
		domain = m_cookie[unitindex].m_domain;
		path = m_cookie[unitindex].m_path;
		sendUseage = m_cookie[unitindex].m_sendUseage;
		isHttpOnly = m_cookie[unitindex].m_isHttpOnly;
		created = m_cookie[unitindex].m_created;
		deadline = m_cookie[unitindex].m_deadline;
		dbcrawl.updateMysql_cookies(cookieid, m_website, cookieKey, cookieValue, domain, path, sendUseage, isHttpOnly, created, deadline);
	}
	return 0;
}

int CCookie::getCookie(int cookieid)
{
	//get from db
	CSingleCrawl *singlecrawl = CSingleCrawl::GetInstance();
	CDBServer dbcrawl = singlecrawl->m_db;
	string cookiessrc = "";
	vector< vector<string> >cookies = dbcrawl.SelectMysql_cookies(cookieid, m_website);
	for(int cookieindex = 0;  cookieindex < cookies.size(); cookieindex++)
	{
		if(cookies[cookieindex].size() >= 10)
		{
			CCookieUnit cookieunit;
			cookieunit.m_cookieKey = cookies[cookieindex][2];
			cookieunit.m_cookieValue = cookies[cookieindex][3];
			cookieunit.m_domain = cookies[cookieindex][4];
			cookieunit.m_path = cookies[cookieindex][5];
			cookieunit.m_sendUseage = cookies[cookieindex][6];
			cookieunit.m_isHttpOnly = atoi(cookies[cookieindex][7].c_str());
			cookieunit.m_created = cookies[cookieindex][8];
			cookieunit.m_deadline = cookies[cookieindex][9];
			//cout<<cookieunit.m_cookieKey<<"="<<cookieunit.m_cookieValue<<endl;
			m_cookie.push_back(cookieunit);
		}
	}
	return 1;
}

void CCookie::getCookieKeyValue(string &keyvalue)
{
	string cookieveyvalue;
	for(int cookieindex = 0; cookieindex < m_cookie.size(); cookieindex++)
	{
		cookieveyvalue.clear();
		m_cookie[cookieindex].getKeyValue(cookieveyvalue);
		keyvalue += cookieveyvalue;
	}
}

void CCookie::setCookie(const string &cookie)
{
	m_cookiesrc = cookie;
}

void CCookie::getCookie(vector<CCookieUnit> &cookie)
{
	cookie = m_cookie;
}
int CCookie::addCookieUnit(const CCookieUnit &cookieunit)
{
	m_cookie.push_back(cookieunit);
	return 1;
}

void CCookie::setWebsite(const string &website)
{
	m_website = website;
}

int CCookie::getWebsite(string &website)
{
	website = m_website;
	return 0;
}
