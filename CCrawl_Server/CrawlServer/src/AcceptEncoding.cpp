/*
 * AcceptEncoding.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "AcceptEncoding.h"

CAcceptEncoding::CAcceptEncoding()
{
	m_acceptEncoding ="";
}

CAcceptEncoding::~CAcceptEncoding()
{
	m_acceptEncoding ="";
}

void CAcceptEncoding::setAcceptEncoding(const string &acceptencoding)
{
	m_acceptEncoding = acceptencoding;
}

string CAcceptEncoding::getAcceptEncoding()
{
	return m_acceptEncoding;
}

