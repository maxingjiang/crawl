/*
 * postLogin.h
 *
 *  Created on: Aug 22, 2016
 *      Author: root
 */

#ifndef CRAWLSERVER_INCLUDE_POSTLOGIN_H_
#define CRAWLSERVER_INCLUDE_POSTLOGIN_H_

#include <iostream>
#include <string>
#include "CCrawl.h"

using namespace std;

class CPostLogin
{
public:
	CPostLogin();
	virtual ~CPostLogin();

	int login(CCrawl *crawl, const string &loginurl, const string &postdata);
	int logout(CCrawl *crawl, const string &loginurl);
};

#endif /* CRAWLSERVER_INCLUDE_POSTLOGIN_H_ */
