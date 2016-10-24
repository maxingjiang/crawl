/*
 * requestMode.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "RequestPostdata.h"

CRequestPostdata::CRequestPostdata()
{
	m_postdata.clear();
}

CRequestPostdata::~CRequestPostdata()
{
	m_postdata.clear();
}

void CRequestPostdata::setPostdata(const string &postdata)
{
	m_postdata = postdata;
}

string CRequestPostdata::getPostdata()
{
	return m_postdata;
}

void CRequestPostdata::sendPostdata(CHttpRequest * httpRequest)
{
    if(!m_postdata.empty())
    {
    	curl_easy_setopt(httpRequest->m_curl, CURLOPT_POSTFIELDS, m_postdata.c_str());
    	curl_easy_setopt(httpRequest->m_curl, CURLOPT_POST, 1);

    	//curl_easy_setopt(httpRequest->m_curl, CURLOPT_VERBOSE, 1L);
    }
    else
    {
    	//curl_easy_setopt(httpRequest->m_curl, CURLOPT_POST, 0);
    }
}
