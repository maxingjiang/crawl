/*
 * CCookieUnit.h
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#ifndef INCLUDE_REQUESTHEADERS_CCookieUnit_H_
#define INCLUDE_REQUESTHEADERS_CCookieUnit_H_

#include <iostream>
#include <string>

using namespace std;

/*
 * example
 * Set-Cookie: H_PS_PSSID=220718; path=/; domain=.baidu.com
 *
*/

class CCookieUnit
{
public:
	CCookieUnit();
	virtual ~CCookieUnit();

    int setCookieUnit(const string &cookieKey, const string &cookieValue, const string &domain,
			const string &path, const string &sendUseage, int isHttpOnly, const string &created, const string &deadline);

    int getCookieUnit(string &cookieKey, string &cookieValue, string &domain,
			string &path, string &sendUseage, int *isHttpOnly, string &created, string &deadline);

    void getKeyValue(string &keyvalue);

public:
    string m_cookieKey;
    string m_cookieValue;
    string m_domain;
    string m_path;
    string m_sendUseage;
    int m_isHttpOnly;
    string m_created;
    string m_deadline;
};

#endif /* INCLUDE_REQUESTHEADERS_CCookieUnit_H_ */


