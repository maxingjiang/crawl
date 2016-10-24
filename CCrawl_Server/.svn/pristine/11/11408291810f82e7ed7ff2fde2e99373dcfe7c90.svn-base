/*
 * CCookieUnit.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "CCookieUnit.h"

CCookieUnit::CCookieUnit()
{
    m_cookieKey.clear();
    m_cookieValue.clear();
    m_domain.clear();
    m_path.clear();
    m_sendUseage.clear();
    m_isHttpOnly = 0;
    m_created.clear();
    m_deadline.clear();
}

CCookieUnit::~CCookieUnit()
{
    m_cookieKey.clear();
    m_cookieValue.clear();
    m_domain.clear();
    m_path.clear();
    m_sendUseage.clear();
    m_isHttpOnly = 0;
    m_created.clear();
    m_deadline.clear();
}

int CCookieUnit::setCookieUnit(const string &cookieKey, const string &cookieValue, const string &domain,
			const string &path, const string &sendUseage, int isHttpOnly, const string &created, const string &deadline)
{
    m_cookieKey = cookieKey;
    m_cookieValue = cookieValue;
    m_domain = domain;
    m_path = path;
    m_sendUseage = sendUseage;
    m_isHttpOnly = isHttpOnly;
    m_created = created;
    m_deadline = deadline;
	return 0;
}

int CCookieUnit::getCookieUnit(string &cookieKey, string &cookieValue, string &domain,
			string &path, string &sendUseage, int *isHttpOnly, string &created, string &deadline)
{
	cookieKey = m_cookieKey;
	cookieValue = m_cookieValue;
	domain = m_domain;
	path = m_path;
	sendUseage = m_sendUseage;
	*isHttpOnly = m_isHttpOnly;
	created = m_created;
	deadline = m_deadline;
	return 0;
}

void CCookieUnit::getKeyValue(string &keyvalue)
{
	keyvalue = m_cookieKey + "=" + m_cookieValue + "; ";
}





