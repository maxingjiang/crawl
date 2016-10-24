/*
 * CCookie.h
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#ifndef INCLUDE_REQUESTHEADERS_CCOOKIE_H_
#define INCLUDE_REQUESTHEADERS_CCOOKIE_H_

#include <iostream>
#include <string>
#include <vector>
#include "CCookieUnit.h"
#include "singleCrawl.h"

using namespace std;

/*
 * example
 * FP=31DD6ADBF50361B334FF588A8ACC1322:FG=1; FP2=3496A4AB4A4C0E6B2EABCB295301A545:FG=1
 *
*/

class CCookie
{
public:
	CCookie();
	virtual ~CCookie();

	int saveCookie(int cookieid = 1);
	int getCookie(int cookieid = 1);

	void getCookie(vector<CCookieUnit> &cookie);
	int addCookieUnit(const CCookieUnit &cookieunit);

	void setWebsite(const string &website);
	int getWebsite(string &website);

	void getCookieKeyValue(string &keyvalue);
    void setCookie(const string &cookie);

private:
    vector<CCookieUnit> m_cookie;
    string m_website;

    string m_cookiesrc; //keyvalue(string)
};

#endif /* INCLUDE_REQUESTHEADERS_CCOOKIE_H_ */
