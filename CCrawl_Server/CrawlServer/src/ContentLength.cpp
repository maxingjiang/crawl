/*
 * ContentLength.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "ContentLength.h"

CContentLength::CContentLength()
{
	m_ContentLength ="";
}

CContentLength::~CContentLength()
{
	m_ContentLength ="";
}

void CContentLength::setContentLength(const string &ContentLength)
{
	m_ContentLength = ContentLength;
}

string CContentLength::getContentLength()
{
	return m_ContentLength;
}

