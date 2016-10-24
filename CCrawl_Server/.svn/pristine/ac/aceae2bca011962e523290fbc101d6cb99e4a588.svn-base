/*
 * responseHeaders.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "CResponseHeaders.h"
#include "singleCrawl.h"
#include "CCookie.h"
#include "common.h"
#include "split.h"
#include "charsetEncode.h"

CResponseHeaders::CResponseHeaders()
{
	m_StatusCode = "";
	m_ContentType = "";
	m_Location = "";
	m_cookieid = 1;
}

CResponseHeaders::~CResponseHeaders()
{
	m_StatusCode = "";
	m_ContentType = "";
	m_Location = "";
	m_cookieid = 1;
}

string CResponseHeaders::getStatusCode()
{
	return m_StatusCode;
}

string CResponseHeaders::getContentType()
{
	return m_ContentType;
}

string CResponseHeaders::getLocation()
{
	return m_Location;
}


void CResponseHeaders::setCookieId(int id)
{
	m_cookieid = id;
}

/*
 * HTTP/1.1 200 OK
 * Content-Type: text/html; charset=utf-8
 * Location: www.baidu.com
 * Set-Cookie: SERVERID=73ea7682c79ff5c414f1e6047449c5c1|1469527448|1469527448;Path=/
 * */
void CResponseHeaders::getResponseparameterFromSrc(const string url, const string &responseheaders)
{
	Csplit cr;
	string domain;
	vector<string> domains = cr.split(url, "/");
	if(domains.size() >= 3)
	{
		domain = domains[2];
	}

	vector<string> header = cr.split(responseheaders, "\r\n");
	vector<string>::iterator iter = header.begin();
	for(; iter != header.end(); iter++)
	{
		vector<string> headerstatus = cr.split(*iter, " ");
		if(headerstatus.size() >= 2 && (*iter).find(RESPONSESTATUSCODE, 0) == 0)//HTTP/1.1 200 OK
		{
			m_StatusCode = headerstatus[1];
			continue;
		}
		vector<string> headersplit = cr.split(*iter, ": ");
		if(headersplit.size() >= 2)
		{
			if((*iter).find(RESPONSECONTENTTYPE, 0) == 0)
			{
				m_ContentType = headersplit[1];
				continue;
			}
			if((*iter).find(RESPONSELOCATION, 0) == 0)
			{
				m_Location = headersplit[1];
				continue;
			}
			if((*iter).find(RESPONSESETCOOKIE, 0) == 0)
			{
				//cout<<"======>set-cookie: "<<headersplit[1]<<endl;

				vector< pair<string, string> >  cookiemap = getCookieKeyValue(headersplit[1]);
				vector< pair<string, string> > ::iterator iter = cookiemap.begin();
				int domainflag = 0;
				for(; iter != cookiemap.end(); iter++)
				{
					if(iter->first == "Domain" || iter->first == "domain")
					{
						domainflag = 1;
						break;
					}
				}
				if(domainflag == 0)
				{
					cookiemap.push_back(pair<string, string>("domain", domain));
				}
				saveResponseCookies(cookiemap);
				continue;
			}
		}
	}
}

//H_PS_PSSID=20719; path=/; domain=.baidu.com
vector< pair<string, string> > CResponseHeaders::getCookieKeyValue(const string &responsecookie)
{
	vector< pair<string, string> > cookiemaps;
	Csplit cr;
	vector<string> cookiesplit = cr.split(responsecookie, ";");

	for(int index = 0; index < cookiesplit.size(); index++)
	{
		vector<string> cookie_key_value = cr.split(cookiesplit[index], "=");

		if(cookie_key_value.size() >= 2)
		{
			string value;
			for(int i = 1; i < cookie_key_value.size(); i++) //BAIDUID=78589AF02BF42883E891C0BEACF3E93E:FG=1
				value += (cookie_key_value[i]+"=");
			value = value.substr(0, value.size() - 1);
			CcharsetEncode encode;
			if(index != 0)
				transform(cookie_key_value[0].begin(),cookie_key_value[0].end(),cookie_key_value[0].begin(),encode.tolower);//all(key) to lower
			if(cookie_key_value[0][0] == ' ')
				cookie_key_value[0] = cookie_key_value[0].substr(1);
			cookiemaps.push_back(pair<string, string>(cookie_key_value[0], value));
			//cout<<"key:value "<<cookie_key_value[0]<<" <=> "<<value<<endl;
		}
		else if(cookie_key_value.size() == 1)
		{
			if(index == 0)//key&value
				cookiemaps.push_back(pair<string, string>(cookie_key_value[0], ""));
			CcharsetEncode encode;
			transform(cookie_key_value[0].begin(),cookie_key_value[0].end(),cookie_key_value[0].begin(),encode.tolower);
			if(cookie_key_value[0][0] == ' ')//remove space
				cookie_key_value[0] = cookie_key_value[0].substr(1);

			if(cookie_key_value[0].find("httponly", 0) == 0)
			{
				cookiemaps.push_back(pair<string, string>(cookie_key_value[0], "1"));
				//cout<<"key:value "<<cookie_key_value[0]<<" <=> "<<"1"<<endl;
			}
		}
	}

	return cookiemaps;
}

void CResponseHeaders::saveResponseCookies(const vector< pair<string, string> >& cookie)
{
	//insert to db
	CSingleCrawl *singlecrawl = CSingleCrawl::GetInstance();
	CDBServer dbcrawl = singlecrawl->m_db;

    time_t curTime = time(NULL);
    tm * gmTime = gmtime(&curTime);
    char strTimeBuf[50];
    strftime(strTimeBuf, 100, " %a, %d %b %Y %X GMT;", gmTime);

	string website = "";
	string cookieKey = "";
	string cookieValue = "";
	string domain = "";
	string path = "/";
	string sendUseage = "all";
	int isHttpOnly = 0;
	string created = strTimeBuf;
	string deadline = "this connection";
	vector< pair<string, string> >::const_iterator cookieiter = cookie.begin();
	if(cookie.size() >= 1) //cookie: key&value
	{
		cookieKey = cookie[0].first;
		cookieValue = cookie[0].second;
	}
	for(cookieiter++; cookieiter != cookie.end(); cookieiter++)
	{
		if(cookieiter->first == "domain")
		{
			domain = cookieiter->second;
			if(domain[0] == '.')
				website = domain.substr(1);
			else
				website = domain;
		}
		else if(cookieiter->first == "path")
		{
			path = cookieiter->second;
		}
		else if(cookieiter->first == "expires")
		{
			deadline = cookieiter->second;
		}
		else if(cookieiter->first == "httponly")
		{
			isHttpOnly = 1;
		}
		else
		{
			//other parameter
			continue;
		}
	}

	CCookie ccookie;
	ccookie.setWebsite(website);

	CCookieUnit cookieunit;
	cookieunit.m_cookieKey = cookieKey;
	cookieunit.m_cookieValue = cookieValue;
	cookieunit.m_domain = domain;
	cookieunit.m_path = path;
	cookieunit.m_sendUseage = sendUseage;
	cookieunit.m_isHttpOnly = isHttpOnly;
	cookieunit.m_created = created;
	cookieunit.m_deadline = deadline;
	ccookie.addCookieUnit(cookieunit);
	ccookie.saveCookie(m_cookieid);

}





