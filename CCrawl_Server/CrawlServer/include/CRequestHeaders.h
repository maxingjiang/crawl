/*
 * CRequestHeaders.h
 *
 *  Created on: Jun 29, 2016
 *      Author: root
 */

#ifndef INCLUDE_CREQUESTHEADERS_H_
#define INCLUDE_CREQUESTHEADERS_H_

#include <iostream>
#include <stdio.h>
#include "CCookie.h"
#include "AcceptEncoding.h"
#include "Accept.h"
#include "UserAgent.h"
#include "Referer.h"
#include "CDBServer.h"
#include "stringList.h"
#include "CHttpRequest.h"
#include "AcceptLanguage.h"
#include "CRequestUrl.h"
#include "CacheControl.h"
#include "ContentLength.h"
#include "ContentType.h"

using namespace std;

//postdata and proxy need set in crawl
class CRequestHeaders
{
public:
	CRequestHeaders();
	virtual ~CRequestHeaders();

	void initHeaders(); //init member
	void setSrcToMember(); //set m_requestHeaders to parameters
	void getRequestHeaders(const string &filename); //get headers from file
	int getRequestHeaders(CDBServer *conn, int requestid, const string &requestUrl); //get headers from mysql (1,"www.baidu.com")

	void sendHeaders(CHttpRequest * httpRequest, CRequestUrl &requesturl);
	void sendHeadersFromFile(CHttpRequest * httpRequest, CRequestUrl &requesturl);

	void sendMultipartPostHeaders(CHttpRequest * httpRequest, CRequestUrl &requesturl, const map<string, string> &multipartdata);

	void setAcceptEncoding(const CAcceptEncoding &AcceptEncoding);
	void getAcceptEncoding(CAcceptEncoding &AcceptEncoding);
	void setAccept(const CAccept &Accept);
	void getAccept(CAccept &Accept);
	void setRequestCookie(const CCookie &RequestCookie);
	void getRequestCookie(CCookie &RequestCookie);
	void setUserAgent(const CUserAgent &UserAgent);
	void getUserAgent(CUserAgent &UserAgent);
	void setReferer(const CReferer &Referer);
	void getReferer(CReferer &Referer);
	void setAcceptLanguage(const CAcceptLanguage &AcceptLanguage);
	void getAcceptLanguage(CAcceptLanguage &AcceptLanguage);
	void setCacheControl(const CCacheControl &CacheControl);
	void getCacheControl(CCacheControl &CacheControl);
	void setContentLength(const CContentLength &ContentLength);
	void getContentLength(CContentLength &ContentLength);
	void setContentType(const CContentType &ContentType);
	void getContentType(CContentType &ContentType);

private:
	CAcceptEncoding m_CAcceptEncoding;
	CAccept m_CAccept;
	CCookie m_CRequestCookie;
	CUserAgent m_CUserAgent;
	CReferer m_CReferer;
	CAcceptLanguage m_acceptLanguage;
	CCacheControl m_CacheControl;
	CContentLength m_ContentLength;
	CContentType m_ContentType;

	CstringList m_requestHeaders;
	string m_requestHeadersfile;
};

#endif /* INCLUDE_CREQUESTHEADERS_H_ */
