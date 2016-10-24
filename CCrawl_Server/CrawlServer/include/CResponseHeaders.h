/*
 * CResponseHeaders.h
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#ifndef INCLUDE_CRESPONSEHEADERS_H_
#define INCLUDE_CRESPONSEHEADERS_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CResponseHeaders
{
public:
	CResponseHeaders();
	virtual ~CResponseHeaders();

	void getResponseparameterFromSrc(const string url, const string &responseheaders);
	void saveResponseCookies(const vector< pair<string, string> >& cookie);
	string getStatusCode();
	string getContentType();
	string getLocation();

	void setCookieId(int id = 1);

private:
	//H_PS_PSSID=20719; path=/; domain=.baidu.com
	vector< pair<string, string> > getCookieKeyValue(const string &responsecookie);

private:
	string m_StatusCode; //200,206
	string m_ContentType; //text/html; charset=utf-8
	string m_Location; //www.baidu.com

	int m_cookieid;
};

#endif /* INCLUDE_CRESPONSEHEADERS_H_ */
