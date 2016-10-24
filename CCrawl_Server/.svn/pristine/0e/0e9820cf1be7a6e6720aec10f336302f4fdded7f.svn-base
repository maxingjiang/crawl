/*
 * CHttpRequest.cpp
 *
 *  Created on: Jul 27, 2016
 *      Author: root
 */

#include "CHttpRequest.h"
#include <stdio.h>

CHttpRequest::CHttpRequest()
{
	m_curl = NULL;
	m_responseHeader.clear();
	m_responseBody.clear();
	m_contentType.clear();
	initCurl();
}

CHttpRequest::~CHttpRequest()
{
	cleanupCurl();
}

void CHttpRequest::initCurl()
{
	if(m_curl == NULL)
	{
		m_curl = curl_easy_init();
	}
}

void CHttpRequest::cleanupCurl()
{
	if(m_curl != NULL)
	{
		curl_easy_cleanup(m_curl);
		m_curl = NULL;
	}
}

void CHttpRequest::initCurlData()
{
    curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "gzip");
}

void CHttpRequest::perform()
{
	curl_easy_perform(m_curl);
}

void CHttpRequest::getHeaderData()
{
	m_responseHeader.clear();
    curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, namespace_split::write_header);
    curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &m_responseHeader);
    curl_easy_setopt(m_curl, CURLOPT_NOBODY, 1L); //not body, post must open
    //curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "HEAD");
}

void CHttpRequest::getWritaData()
{
	m_responseBody.clear();
	m_responseHeader.clear();
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, namespace_split::write_data);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_responseBody);
    curl_easy_setopt(m_curl, CURLOPT_NOBODY, 0L);
}

void CHttpRequest::getWritaDataToFile(const string &filename)
{
    //int pos = filename.find_last_of('/');
    //string loadfile = "./"+filename.substr(filename.length() - pos, filename.length());
    //cout<<"loadfile: "<<loadfile<<endl;
    FILE *fp;
    if ((fp = fopen(filename.c_str(), "w")) == NULL)
        return;
	m_responseBody.clear();
	m_responseHeader.clear();
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(m_curl, CURLOPT_NOBODY, 0L);
}

void CHttpRequest::getContentType()
{
    char *contype = NULL;
    curl_easy_getinfo(m_curl, CURLINFO_CONTENT_TYPE, &contype);
    //cout<<"content type: "<<contype<<endl;
    if(contype == NULL)
    {
		m_responseHeader = "";
		m_responseBody = "";
		return ;
    }
    m_contentType = contype;
}



