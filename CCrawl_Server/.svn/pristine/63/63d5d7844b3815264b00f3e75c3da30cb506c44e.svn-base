/*
 * CCrawl.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "CCrawl.h"
#include <exception>

CCrawl::CCrawl():m_CRequestUrl(), m_requestheaders(), m_responseheaders(), m_CRequestPostdata()
{
	m_httpRequest = new CHttpRequest();
	m_requestMode = GET;
	m_inuse = 0;
	m_locationJumpTimes = 0;
}

CCrawl::~CCrawl()
{
	delete m_httpRequest;
	m_requestMode = GET;
}

int CCrawl::getResponseData()
{
	try
	{
	sendUrl(m_httpRequest);
	sendHeaders(m_httpRequest);
	m_httpRequest->initCurlData();
	sendProxy(m_httpRequest);
	m_httpRequest->getHeaderData();
	if(m_requestMode == GET)
	{
        LOG4CPLUS_DEBUG(ClogCPP::m_logger,"http request mode: GET");
		m_httpRequest->perform();
		m_httpRequest->getContentType();
	    if(m_httpRequest->m_contentType.find("text", 0) == 0)
	    {
			m_httpRequest->getWritaData();
			m_httpRequest->perform();
	    }
	    else if(m_httpRequest->m_contentType.find("image", 0) == 0) //app faild
	    {
			string cmd = string("wget -P ./ ")+m_CRequestUrl.getCRequestUrl();
			//cout<<cmd<<endl;
			system(cmd.c_str());
			//m_httpRequest->getWritaDataToFile(m_CRequestUrl.getFilename());
			//m_httpRequest->perform();
	    }
	}
	if(m_requestMode == POST)
	{
        LOG4CPLUS_DEBUG(ClogCPP::m_logger,"http request mode: POST");
		sendPostdata(m_httpRequest);
		m_httpRequest->getWritaData();
		m_httpRequest->perform();
	}
	}catch(std::exception &e)
	{
		cout<<e.what()<<endl;
		return 0;
	}catch(...)
	{
		printf("error catch! \n");
		return 0;
	}

}

int CCrawl::response_status_function()
{
	m_responseheaders.getResponseparameterFromSrc(m_CRequestUrl.getCRequestUrl(), m_httpRequest->m_responseHeader);

	int status_code = 0;
	status_code = atoi(m_responseheaders.getStatusCode().c_str());
	LOG4CPLUS_DEBUG(ClogCPP::m_logger, status_code);
	return status_code;
	switch(status_code)
	{
	case 200:
		response_return_code_200();
		break;
	case 204:
		response_return_code_204();
		break;
	case 206:
		response_return_code_206();
		break;
	case 301:
		response_return_code_301();
		break;
	case 302:
		response_return_code_302();
		break;
	case 303:
		response_return_code_303();
		break;
	case 304:
		response_return_code_304();
		break;
	case 307:
		response_return_code_307();
		break;
	case 400:
		response_return_code_400();
		break;
	case 401:
		response_return_code_401();
		break;
	case 403:
		response_return_code_403();
		break;
	case 404:
		response_return_code_404();
		break;
	case 405:
		response_return_code_200();
		break;
	case 500:
		response_return_code_500();
		break;
	case 503:
		response_return_code_503();
		break;
	default:
		break;
	}
	return status_code;
}

int CCrawl::GET_Html(const string &url, const string &imagefilename)
{
	setRequestMode(GET);
	m_CRequestUrl.setCRequestUrl(url);
	m_CRequestUrl.setFilename(imagefilename);

	try
	{
		sendUrl(m_httpRequest);
		sendHeaders(m_httpRequest);
		m_httpRequest->initCurlData();
		sendProxy(m_httpRequest);
		m_httpRequest->getHeaderData();
		m_httpRequest->perform();
		m_httpRequest->getContentType();
	    if(m_httpRequest->m_contentType.find("text", 0) == 0)
	    {
			m_httpRequest->getWritaData();
			m_httpRequest->perform();
	    }
	    else if(m_httpRequest->m_contentType.find("image", 0) == 0) //img
	    {
			string cmd = string("wget -P ./ ")+m_CRequestUrl.getCRequestUrl();
			//cout<<cmd<<endl;
			system(cmd.c_str());
			//m_httpRequest->getWritaDataToFile(m_CRequestUrl.getFilename());
			//m_httpRequest->perform();
	    }

	}catch(std::exception &e)
	{
		cout<<e.what()<<endl;
		return 0;
	}catch(...)
	{
		printf("error catch! \n");
		return 0;
	}
	return response_status_function();
}

int CCrawl::POST_data_Html(const string &url, const string &postdata)
{
	setRequestMode(POST);
	m_CRequestUrl.setCRequestUrl(url);
	m_CRequestPostdata.setPostdata(postdata);
	try
	{
		sendUrl(m_httpRequest);
		sendHeaders(m_httpRequest);
		m_httpRequest->initCurlData();
		sendProxy(m_httpRequest);
		m_httpRequest->getHeaderData();
		sendPostdata(m_httpRequest);
		m_httpRequest->getWritaData();
		m_httpRequest->perform();

	}catch(std::exception &e)
	{
		cout<<e.what()<<endl;
		return 0;
	}catch(...)
	{
		printf("error catch! \n");
		return 0;
	}
	return response_status_function();
}

int CCrawl::POST_multipart_Html(const string &url, const map<string, string> &multipartdata)
{
	setRequestMode(POST_multipart);
	m_CRequestUrl.setCRequestUrl(url);
	try
	{
		sendUrl(m_httpRequest);
		sendMultipartHeaders(m_httpRequest, multipartdata);
		m_httpRequest->initCurlData();
		sendProxy(m_httpRequest);
		m_httpRequest->getHeaderData();
		m_httpRequest->getWritaData();
		m_httpRequest->perform();

	}catch(std::exception &e)
	{
		cout<<e.what()<<endl;
		return 0;
	}catch(...)
	{
		printf("error catch! \n");
		return 0;
	}
	return response_status_function();
}

void CCrawl::getRequestUrl(string &url)
{
	url =  m_CRequestUrl.getCRequestUrl();
}

void CCrawl::response_return_code_200()
{
	return ;
}

void CCrawl::response_return_code_204()
{
    //not content,return
	return ;
}

void CCrawl::response_return_code_206() // modify
{
	//return partial content
	return ;
}

void CCrawl::response_return_code_301()
{
	m_locationJumpTimes += 1;
	if(m_locationJumpTimes > LOCATION_JUMP_NUMS)
	{
		return ;
	}
	string url = m_responseheaders.getLocation();
	m_CRequestUrl.setCRequestUrl(url);
	switch(m_requestMode)
	{
	case GET:
		GET_Html(url, "");
		break;
	case POST:
		break;
	case POST_multipart:
		break;

	}
}

void CCrawl::response_return_code_302()
{
	m_locationJumpTimes += 1;
	if(m_locationJumpTimes > LOCATION_JUMP_NUMS)
	{
		return ;
	}
	string url = m_responseheaders.getLocation();
	cout<<"url: "<<url<<endl;
	m_CRequestUrl.setCRequestUrl(url);
	switch(m_requestMode)
	{
	case GET:
		GET_Html(url, "");
		break;
	case POST:
		break;
	case POST_multipart:
		break;

	}
}

void CCrawl::response_return_code_303()
{
	m_locationJumpTimes += 1;
	if(m_locationJumpTimes > LOCATION_JUMP_NUMS)
	{
		return ;
	}
	string url = m_responseheaders.getLocation();
	m_CRequestUrl.setCRequestUrl(url);
	switch(m_requestMode)
	{
	case GET:
		GET_Html(url, "");
		break;
	case POST:
		break;
	case POST_multipart:
		break;

	}
}

void CCrawl::response_return_code_304()
{
	//Not Modified
    return ;
}

void CCrawl::response_return_code_307()
{
	m_locationJumpTimes += 1;
	if(m_locationJumpTimes > LOCATION_JUMP_NUMS)
	{
		return ;
	}
	string url = m_responseheaders.getLocation();
	m_CRequestUrl.setCRequestUrl(url);
	switch(m_requestMode)
	{
	case GET:
		GET_Html(url, "");
		break;
	case POST:
		break;
	case POST_multipart:
		break;

	}
}

void CCrawl::response_return_code_400()
{
    //bad request
	return ;
}

void CCrawl::response_return_code_401() // modify
{
    //request need authentication
	return ;
}

void CCrawl::response_return_code_403()
{
    //forbidden
	return ;
}

void CCrawl::response_return_code_404()
{
    //request not found
	return ;
}

void CCrawl::response_return_code_500()
{
    //Internal Server Error
	return ;
}

void CCrawl::response_return_code_503()
{
    //Service Unavailable
	return ;
}

string CCrawl::getDomainFromUrl(const string &url)
{
	string domain;
	Csplit cr;
	vector<string> domains = cr.split(url, "/");
	if(domains.size() >= 3)
	{
		domain = domains[2];
	}
	//cout<<"domain: "<<domain<<endl;
	return domain;
}

void CCrawl::sendUrl(CHttpRequest * httpRequest)
{
	curl_easy_setopt(httpRequest->m_curl, CURLOPT_URL, m_CRequestUrl.getCRequestUrl().c_str());
	string domain = getDomainFromUrl(m_CRequestUrl.getCRequestUrl().c_str());
	string cookiefilename = domain + "_cookie.txt";
    //cout<<"======cookie:========>"<<cookiefilename<<endl;
	//初始化cookie引擎
	curl_easy_setopt(httpRequest->m_curl, CURLOPT_COOKIEJAR, (char*)cookiefilename.c_str()); //把服务器发过来的cookie保存到xxx_cookie.txt
	curl_easy_setopt(httpRequest->m_curl, CURLOPT_COOKIEFILE, (char*)cookiefilename.c_str()); //读取本地存储的cookie
	curl_easy_setopt(httpRequest->m_curl,CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(httpRequest->m_curl, CURLOPT_MAXREDIRS, 3);
}

void CCrawl::sendHeaders(CHttpRequest * httpRequest)
{
	m_requestheaders.sendHeaders(httpRequest, m_CRequestUrl);
}

void CCrawl::sendMultipartHeaders(CHttpRequest * httpRequest, const map<string, string> &multipartdata)
{
	m_requestheaders.sendMultipartPostHeaders(httpRequest, m_CRequestUrl, multipartdata);
}

void CCrawl::sendPostdata(CHttpRequest * httpRequest)
{
	m_CRequestPostdata.sendPostdata(httpRequest);
}

void CCrawl::sendProxy(CHttpRequest * httpRequest)
{
	m_CProxy.sendProxy(httpRequest);
}

void CCrawl::getRequestHeaders(CRequestHeaders &requestHeaders)
{
	requestHeaders = m_requestheaders;
}

void CCrawl::getResponseHeaders(CResponseHeaders &responseHeaders)
{
	responseHeaders = m_responseheaders;
}

int CCrawl::getResponseHeaders(string &headers)
{
	headers = m_httpRequest->m_responseHeader;
	return atoi(m_responseheaders.getStatusCode().c_str());
}

int CCrawl::getResponseBody(string &body)
{
	string data = m_httpRequest->m_responseBody;

	CPPregex regex;
	string charset;
	regex.getCharset(data, charset, "<meta.*?[cC][hH][aA][rR][sS][eE][tT]=['\"]?(.*?)['\"]");
	//cout<<"charset: "<<charset<<endl;

	CcharsetEncode cc;
	body = cc.encode_to_utf8(data);
	cc.unicode_to_utf8(body);
	return atoi(m_responseheaders.getStatusCode().c_str());
}

void CCrawl::setRequestHeaders(const CRequestHeaders &requestHeaders)
{
	m_requestheaders = requestHeaders;
}

void CCrawl::setProxy(const CProxy &proxy)
{
	m_CProxy = proxy;
}

void CCrawl::setRequestMode(const request_mode &requestmode)
{
    m_requestMode = requestmode;
}

int CCrawl::login(const string &loginurl, const string &postdata)
{
	int statuscode = POST_data_Html(loginurl, postdata);
	string headers;
	getResponseHeaders(headers);
	cout<<headers<<endl;
	return statuscode;
}

void CCrawl::setHttpRequestInit()
{
	m_httpRequest->initCurl();
}

void CCrawl::setHttpRequestCleanup()
{
	m_httpRequest->cleanupCurl();
}




