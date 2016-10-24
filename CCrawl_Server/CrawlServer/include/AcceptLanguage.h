/*
 * AcceptLanguage.h
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#ifndef INCLUDE_REQUESTHEADERS_AcceptLanguage_H_
#define INCLUDE_REQUESTHEADERS_AcceptLanguage_H_

#include <iostream>
#include <string>

using namespace std;

/*
 * example
 * Accept-Language: zh-CN,zh;q=0.8
 *
*/

class CAcceptLanguage
{
public:
	CAcceptLanguage();
	~CAcceptLanguage();

    void setAcceptLanguage(const string &acceptlanguage);
    string getAcceptLanguage();
private:
	string m_acceptLanguage;
};

#endif /* INCLUDE_REQUESTHEADERS_AcceptLanguage_H_ */
