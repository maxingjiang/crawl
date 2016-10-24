/*
 * CCrawl.h
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#ifndef INCLUDE_CCRAWL_H_
#define INCLUDE_CCRAWL_H_

#include "common.h"
#include "CRequestHeaders.h"
#include "CResponseHeaders.h"
#include "Proxy.h"
#include "log4cpp.h"
#include "RequestPostdata.h"
#include "CRequestUrl.h"
#include "split.h"
#include "CHttpRequest.h"
#include "charsetEncode.h"
#include "CPPregex.h"

class CCrawl
{
public:
	CCrawl();
	virtual ~CCrawl();
	//GET mode,if content is text, return content, if content is image, write to file, if content is vedio, nothing to do.
	int GET_Html(const string &url, const string &imagefilename);
	//POST data mode
	int POST_data_Html(const string &url, const string &postdata);
	//POST multipart mode
	int POST_multipart_Html(const string &url, const map<string, string> &multipartdata);

	void getRequestUrl(string &url); //get url
	void getRequestHeaders(CRequestHeaders &requestHeaders); //return requestHeader class
	void getResponseHeaders(CResponseHeaders &responseHeaders); //return responseheader class

	int getResponseHeaders(string &headers);
	int getResponseBody(string &body);

	void setRequestHeaders(const CRequestHeaders &requestHeaders); //set
	void setProxy(const CProxy &proxy);
	void setHttpRequestInit(); //init libcurl
	void setHttpRequestCleanup(); //cleanup libcurl

	void setRequestMode(const request_mode &requestmode);

private:

	int getResponseData();

	void sendUrl(CHttpRequest * httpRequest);
	void sendHeaders(CHttpRequest * httpRequest);
	void sendMultipartHeaders(CHttpRequest * httpRequest, const map<string, string> &multipartdata);
	void sendPostdata(CHttpRequest * httpRequest);
	void sendProxy(CHttpRequest * httpRequest);

	int response_status_function();
	void response_return_code_200();
	void response_return_code_204();
	void response_return_code_206();
	void response_return_code_301();
	void response_return_code_302();
	void response_return_code_303();
	void response_return_code_304();
	void response_return_code_307();
	void response_return_code_400();
	void response_return_code_401();
	void response_return_code_403();
	void response_return_code_404();
	void response_return_code_500();
	void response_return_code_503();

	string getDomainFromUrl(const string &url);

public:
	int login(const string &loginurl, const string &postdata);

private:
	CRequestUrl m_CRequestUrl;
	CRequestHeaders m_requestheaders;
	CResponseHeaders m_responseheaders;

	CProxy m_CProxy;
	CRequestPostdata m_CRequestPostdata;
    CHttpRequest * m_httpRequest;
    request_mode m_requestMode;
    int m_locationJumpTimes;

public:
    int m_inuse; //tab the crawler is in use or not
};

#endif /* INCLUDE_CCRAWL_H_ */
