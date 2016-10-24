/*
 * ContentType.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "ContentType.h"

CContentType::CContentType()
{
	m_ContentType ="";
}

CContentType::~CContentType()
{
	m_ContentType ="";
}

void CContentType::setContentType(const string &ContentType)
{
	m_ContentType = ContentType;
}

string CContentType::getContentType()
{
	return m_ContentType;
}

