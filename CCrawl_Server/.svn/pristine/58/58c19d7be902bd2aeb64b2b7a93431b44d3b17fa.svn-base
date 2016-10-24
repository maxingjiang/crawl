/*
 * postLogin.cpp
 *
 *  Created on: Aug 22, 2016
 *      Author: root
 */

#include "postLogin.h"

CPostLogin::CPostLogin()
{

}

CPostLogin::~CPostLogin()
{

}

int CPostLogin::login(CCrawl *crawl, const string &loginurl, const string &postdata)
{
	int statuscode = crawl->POST_data_Html(loginurl, postdata);
	return statuscode;
}

int CPostLogin::logout(CCrawl *crawl, const string &loginurl)
{
	int statuscode = crawl->GET_Html(loginurl, "aaa.png");
	return statuscode;
}

