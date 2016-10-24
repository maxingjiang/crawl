/*
 * CCookies.h
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#ifndef INCLUDE_REQUESTHEADERS_CCOOKIES_H_
#define INCLUDE_REQUESTHEADERS_CCOOKIES_H_

#include <iostream>
#include <string>
#include <vector>
#include "CCookie.h"

using namespace std;

/*
 * example
 * FP=31DD6ADBF50361B334FF588A8ACC1322:FG=1; FP2=3496A4AB4A4C0E6B2EABCB295301A545:FG=1
 *
*/

class CCookies
{
public:
	CCookies();
	virtual ~CCookies();

    int getCookies(); //cookieid is need

    void getCookies(vector<CCookie> &cookies);

	void setCookieId(int cookieid = 1);
	int getCookieId();


private:
	vector<CCookie> m_cookies;
    int m_cookieid;
};

#endif /* INCLUDE_REQUESTHEADERS_CCOOKIES_H_ */
