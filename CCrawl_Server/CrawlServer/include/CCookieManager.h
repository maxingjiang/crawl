/*
 * CCookieManager.h
 *
 *  Created on: Aug 12, 2016
 *      Author: root
 */

#ifndef CRAWLSERVER_INCLUDE_CCOOKIEMANAGER_H_
#define CRAWLSERVER_INCLUDE_CCOOKIEMANAGER_H_

#include <iostream>
#include <vector>
#include <string>
#include "CCookies.h"

using namespace std;

class CCookieManager
{
public:
	CCookieManager();
	virtual ~CCookieManager();

	int getCookiesMgr();
	void getCookiesMgr(vector<CCookies> &cookiesMgr);

private:
	vector<CCookies> m_cookiesMgr;
};

#endif /* CRAWLSERVER_INCLUDE_CCOOKIEMANAGER_H_ */
