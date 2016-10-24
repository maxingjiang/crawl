/*
 * CHttpRequest.h
 *
 *  Created on: Jul 27, 2016
 *      Author: root
 */

#ifndef CRAWLSERVER_INCLUDE_CHTTPREQUEST_H_
#define CRAWLSERVER_INCLUDE_CHTTPREQUEST_H_

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include "split.h"

using namespace std;

class CHttpRequest
{
public:
	CHttpRequest();
	~CHttpRequest();

	void initCurl();
	void cleanupCurl();
	void initCurlData();
	void perform();
	void getHeaderData();
	void getWritaData();
	void getContentType();

	void getWritaDataToFile(const string &filename);

public:
	CURL *m_curl;
	//string m_url; //current url
	string m_responseHeader;
	string m_responseBody;
	string m_contentType;
};

#endif /* CRAWLSERVER_INCLUDE_CHTTPREQUEST_H_ */
