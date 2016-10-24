/*
 * CRequestHeaders.cpp
 *
 *  Created on: Jun 29, 2016
 *      Author: root
 */
#include "CRequestHeaders.h"
#include <sys/file.h>
#include <unistd.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "CCookie.h"

CRequestHeaders::CRequestHeaders()
{
	initHeaders();
	m_requestHeadersfile.clear();
	m_requestHeaders.m_CstringList.clear();
}

CRequestHeaders::~CRequestHeaders()
{
	m_CAcceptEncoding.setAcceptEncoding("");
	m_CAccept.setAccept("");
	m_CUserAgent.setUserAgent("");
	m_CReferer.setReferer("");
	m_CacheControl.setCacheControl("");
	m_ContentLength.setContentLength("");
	m_ContentType.setContentType("");
	m_CRequestCookie.setCookie("");
	m_requestHeadersfile.clear();
	m_requestHeaders.m_CstringList.clear();
}

void CRequestHeaders::getRequestHeaders(const string &filename)
{
	CstringList requestHeaders;
	const int LINE_LENGTH = 1024;
	char src[LINE_LENGTH+1];
    string str;
    FILE *fp = fopen(filename.c_str(), "r");
    if(!fp)
    {
        printf("error file %s \n", filename.c_str());
    }
    while(1)
    {
    	// 加锁以判断文件是否已经被加锁了
    	if(flock(fileno(fp), LOCK_EX | LOCK_NB) == 0)
        {
    		//printf("file %s is unlock status \n", filename.c_str());
        	while ((fgets (src, LINE_LENGTH, fp)) != NULL)
            {
            	str = src;
            	size_t n = str.find_last_not_of(" \r\n\t");
                //std::cout << "src: "<< str << std::endl;
                if( n != string::npos )
                {
                	str.erase( n + 1 , str.size() - n );
                }
                requestHeaders.m_CstringList.push_back(str);
                m_requestHeaders.m_CstringList.push_back(str);
            }
            fclose(fp);
            flock(fileno(fp), LOCK_UN);
            break;
        }
        else
        {
        	printf("file %s is locked, please wait \n", filename.c_str());
        	sleep(1);
        }
    }
}

int CRequestHeaders::getRequestHeaders(CDBServer *conn, int requestid, const string &requestUrl)
{
	if(conn == NULL)
	{
		cout<<__FILE__<<__LINE__<<"conn is NULL"<<endl;
	}
	CstringList requestHeaders;
	requestHeaders.m_CstringList.clear();

	Connection *connect = conn->getConnection();
	if(!connect){
		cout <<__FILE__<<__LINE__<< "getConnection NULL pointer" << endl;
		exit(-1);
	}
	vector< vector<string> > mysqldata = conn->SelectMysql(requestid, requestUrl);
	conn->releaseConnection();

	string headerKeyValue;
	int row = mysqldata.size();
	for(int rownum = 0; rownum < row; rownum++)
	{
		headerKeyValue.clear();
		int column = mysqldata[rownum].size();
		if(column < 4)
		{
			return row;
		}
		if(mysqldata[rownum][2].size() > 0 && mysqldata[rownum][3].size() > 0)
		{
			string localsrc = mysqldata[rownum][2];
			headerKeyValue = mysqldata[rownum][2]+": "+mysqldata[rownum][3];
			requestHeaders.m_CstringList.push_back(headerKeyValue);
			m_requestHeaders.m_CstringList.push_back(headerKeyValue);
			//cout<< headerKeyValue<<endl;
		}
	}
	return row;
}

void CRequestHeaders::initHeaders()
{
	m_CAcceptEncoding.setAcceptEncoding(REQUEST_AcceptEncoding);
	m_CAccept.setAccept(REQUEST_Accept);
	m_acceptLanguage.setAcceptLanguage(REQUEST_AcceptLanguage);
	m_CRequestCookie.setCookie(REQUEST_Cookie);
	m_CUserAgent.setUserAgent(REQUEST_UserAgent);
	m_CReferer.setReferer(REQUEST_Referer);
	m_CacheControl.setCacheControl(REQUEST_CacheControl);
	m_ContentLength.setContentLength(REQUEST_ContentLength);
	m_ContentType.setContentType(REQUEST_ContentType);
	m_CRequestCookie.setCookie(REQUEST_Cookie);
}

void CRequestHeaders::setSrcToMember()
{
	vector<string>::iterator iter = m_requestHeaders.m_CstringList.begin();
	for(; iter != m_requestHeaders.m_CstringList.end(); iter++)
	{
		if((*iter).find(REQUEST_AcceptEncoding, 0) == 0)
		{
			m_CAcceptEncoding.setAcceptEncoding(*iter);
			continue;
		}
		if((*iter).find(REQUEST_Accept, 0) == 0)
		{
			m_CAccept.setAccept(*iter);
			continue;
		}
		if((*iter).find(REQUEST_Cookie, 0) == 0)
		{
			m_CRequestCookie.setCookie(*iter);
			continue;
		}
		if((*iter).find(REQUEST_UserAgent, 0) == 0)
		{
			m_CUserAgent.setUserAgent(*iter);
			continue;
		}
		if((*iter).find(REQUEST_Referer, 0) == 0)
		{
			m_CReferer.setReferer(*iter);
			continue;
		}
		if((*iter).find(REQUEST_AcceptLanguage, 0) == 0)
		{
			m_acceptLanguage.setAcceptLanguage(*iter);
			continue;
		}
	}
}

void CRequestHeaders::sendHeaders(CHttpRequest * httpRequest, CRequestUrl &requesturl)
{
	//sendHeadersFromFile(httpRequest, requesturl);
	//return;
	string domain = "";
	string Origin = "";
	Csplit cr;
	vector<string> domains = cr.split(requesturl.getCRequestUrl(), "/");
	if(domains.size() >= 3)
	{
		domain = domains[2];
		Origin = domains[0] + "//" + domains[2];
	}

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, m_CAcceptEncoding.getAcceptEncoding().c_str());
    headers = curl_slist_append(headers, m_CAccept.getAccept().c_str());
    headers = curl_slist_append(headers, m_CUserAgent.getUserAgent().c_str());
    headers = curl_slist_append(headers, m_acceptLanguage.getAcceptLanguage().c_str());
    headers = curl_slist_append(headers, m_CacheControl.getCacheControl().c_str());
    //headers = curl_slist_append(headers, m_ContentLength.getContentLength().c_str());
    //headers = curl_slist_append(headers, m_ContentType.getContentType().c_str());
    headers = curl_slist_append(headers, m_CReferer.getReferer().c_str());
    headers = curl_slist_append(headers, (string("Host: ")+domain).c_str());
    //headers = curl_slist_append(headers, (string("Origin: ")+Origin).c_str()); //post need
    headers = curl_slist_append(headers, "Connection: keep-alive");
    headers = curl_slist_append(headers, "Upgrade-Insecure-Requests: 1"); //support https
    /*
    cout<<"send headers======>"<<endl;
    cout<<m_CAcceptEncoding.getAcceptEncoding()<<endl;
    cout<<m_CAccept.getAccept()<<endl;
    cout<<m_CUserAgent.getUserAgent()<<endl;
    cout<<m_acceptLanguage.getAcceptLanguage()<<endl;
    cout<<m_CacheControl.getCacheControl()<<endl;
    cout<<m_ContentLength.getContentLength()<<endl;
    cout<<m_ContentType.getContentType()<<endl;
    cout<<m_CReferer.getReferer()<<endl;
    cout<<(string("Host: ")+domain)<<endl;
    cout<<(string("Origin: ")+Origin)<<endl;
    */
    m_CRequestCookie.setWebsite(domain);
    m_CRequestCookie.getCookie(1);
	string cookie;
    m_CRequestCookie.getCookieKeyValue(cookie);
    //headers = curl_slist_append(headers, cookie.c_str());
    curl_easy_setopt(httpRequest->m_curl, CURLOPT_HTTPHEADER, headers);
}

void CRequestHeaders::sendHeadersFromFile(CHttpRequest * httpRequest, CRequestUrl &requesturl)
{
    string filename = "header.txt";
    const int LINE_LENGTH = 1024;
    char str[LINE_LENGTH];
    ifstream fin(filename.c_str());
    struct curl_slist *headers = NULL;
    while( fin.getline(str,LINE_LENGTH))
    {
    	headers = curl_slist_append(headers, str);
    }
    fin.close();
    curl_easy_setopt(httpRequest->m_curl, CURLOPT_HTTPHEADER, headers);
}

void CRequestHeaders::sendMultipartPostHeaders(CHttpRequest * httpRequest, CRequestUrl &requesturl, const map<string, string> &multipartdata)
{
	getRequestHeaders("a.txt");
	struct curl_slist *headers = NULL;
	for(int i = 0; i < m_requestHeaders.m_CstringList.size(); i++)
	{
		cout<<m_requestHeaders.m_CstringList[i]<<endl;
		headers = curl_slist_append(headers, m_requestHeaders.m_CstringList[i].c_str());
	}
	curl_easy_setopt(httpRequest->m_curl, CURLOPT_HTTPHEADER, headers);
	struct curl_httppost *post=NULL;
	struct curl_httppost *last=NULL;
	map<string, string>::const_iterator iterdata = multipartdata.begin();
	for(; iterdata != multipartdata.end(); iterdata++)
	{
		cout<<iterdata->first<<", "<<iterdata->second<<endl;
		curl_formadd(&post, &last, CURLFORM_PTRNAME, (iterdata->first).c_str(), CURLFORM_PTRCONTENTS, (iterdata->second).c_str(), CURLFORM_END);
	}
	/*
	curl_formadd(&post, &last, CURLFORM_PTRNAME, "formhash", CURLFORM_PTRCONTENTS, "0a271710", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_PTRNAME, "company", CURLFORM_PTRCONTENTS, "cumt", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_PTRNAME, "privacy[company]", CURLFORM_PTRCONTENTS, "0", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_PTRNAME, "occupation", CURLFORM_PTRCONTENTS, "it", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_PTRNAME, "privacy[occupation]", CURLFORM_PTRCONTENTS, "0", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_PTRNAME, "position", CURLFORM_PTRCONTENTS, "kf3", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_PTRNAME, "privacy[position]", CURLFORM_PTRCONTENTS, "0", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_PTRNAME, "revenue", CURLFORM_PTRCONTENTS, "20", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_PTRNAME, "privacy[revenue]", CURLFORM_PTRCONTENTS, "0", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_PTRNAME, "profilesubmit", CURLFORM_PTRCONTENTS, "true", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_PTRNAME, "profilesubmitbtn", CURLFORM_PTRCONTENTS, "true", CURLFORM_END);
	*/
	curl_easy_setopt(httpRequest->m_curl, CURLOPT_HTTPPOST, post);
	cout<<"===aaa===="<<endl;
	return;
	string domain = "";
	string Origin = "";
	Csplit cr;
	vector<string> domains = cr.split(requesturl.getCRequestUrl(), "/");
	if(domains.size() >= 3)
	{
		domain = domains[2];
		Origin = domains[0] + "//" + domains[2];
	}

   // struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, m_CAcceptEncoding.getAcceptEncoding().c_str());
    headers = curl_slist_append(headers, m_CAccept.getAccept().c_str());
    headers = curl_slist_append(headers, m_CUserAgent.getUserAgent().c_str());
    headers = curl_slist_append(headers, m_acceptLanguage.getAcceptLanguage().c_str());
    headers = curl_slist_append(headers, m_CacheControl.getCacheControl().c_str());
    headers = curl_slist_append(headers, m_ContentLength.getContentLength().c_str());
    headers = curl_slist_append(headers, m_ContentType.getContentType().c_str());
    headers = curl_slist_append(headers, m_CReferer.getReferer().c_str());
    headers = curl_slist_append(headers, (string("Host: ")+domain).c_str());
    headers = curl_slist_append(headers, (string("Origin: ")+Origin).c_str()); //post need
    headers = curl_slist_append(headers, "Connection: keep-alive");
    headers = curl_slist_append(headers, "Upgrade-Insecure-Requests: 1"); //support https
    string cookie;
    m_CRequestCookie.getCookieKeyValue(cookie);
    headers = curl_slist_append(headers, cookie.c_str());
    curl_easy_setopt(httpRequest->m_curl, CURLOPT_HTTPHEADER, headers);
}

void CRequestHeaders::setAcceptEncoding(const CAcceptEncoding &AcceptEncoding)
{
	m_CAcceptEncoding = AcceptEncoding;
}

void CRequestHeaders::getAcceptEncoding(CAcceptEncoding &AcceptEncoding)
{
	AcceptEncoding = m_CAcceptEncoding;
}

void CRequestHeaders::setAccept(const CAccept &Accept)
{
	m_CAccept = Accept;
}

void CRequestHeaders::getAccept(CAccept &Accept)
{
	Accept = m_CAccept;
}

void CRequestHeaders::setRequestCookie(const CCookie &RequestCookie)
{
	m_CRequestCookie = RequestCookie;
}

void CRequestHeaders::getRequestCookie(CCookie &RequestCookie)
{
	RequestCookie = m_CRequestCookie;
}

void CRequestHeaders::setUserAgent(const CUserAgent &UserAgent)
{
	m_CUserAgent = UserAgent;
}

void CRequestHeaders::getUserAgent(CUserAgent &UserAgent)
{
	UserAgent = m_CUserAgent;
}

void CRequestHeaders::setReferer(const CReferer &Referer)
{
	m_CReferer = Referer;
}

void CRequestHeaders::getReferer(CReferer &Referer)
{
	Referer = m_CReferer;
}

void CRequestHeaders::setAcceptLanguage(const CAcceptLanguage &AcceptLanguage)
{
	m_acceptLanguage = AcceptLanguage;
}

void CRequestHeaders::getAcceptLanguage(CAcceptLanguage &AcceptLanguage)
{
	AcceptLanguage = m_acceptLanguage;
}

void CRequestHeaders::setCacheControl(const CCacheControl &CacheControl)
{
	m_CacheControl = CacheControl;
}

void CRequestHeaders::getCacheControl(CCacheControl &CacheControl)
{
	CacheControl = m_CacheControl;
}

void CRequestHeaders::setContentLength(const CContentLength &ContentLength)
{
	m_ContentLength = ContentLength;
}

void CRequestHeaders::getContentLength(CContentLength &ContentLength)
{
	ContentLength = m_ContentLength;
}

void CRequestHeaders::setContentType(const CContentType &ContentType)
{
	m_ContentType = ContentType;
}

void CRequestHeaders::getContentType(CContentType &ContentType)
{
	ContentType = m_ContentType;
}



