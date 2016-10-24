/*
 * Accept.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "Accept.h"

CAccept::CAccept()
{
	m_accept ="";
}

CAccept::~CAccept()
{
	m_accept ="";
}

void CAccept::setAccept(const string &accept)
{
	m_accept = accept;
}

string CAccept::getAccept()
{
	return m_accept;
}

