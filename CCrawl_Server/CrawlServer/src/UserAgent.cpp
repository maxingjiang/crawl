/*
 * CUserAgent.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "UserAgent.h"

CUserAgent::CUserAgent()
{
	m_useragent = "";
}

CUserAgent::~CUserAgent()
{
	m_useragent = "";
}

void CUserAgent::setUserAgent(const string &useragent)
{
	m_useragent = useragent;
}

string CUserAgent::getUserAgent()
{
	return m_useragent;
}

