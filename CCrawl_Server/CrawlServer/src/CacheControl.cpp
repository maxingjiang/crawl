/*
 * CacheControl.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "CacheControl.h"

CCacheControl::CCacheControl()
{
	m_CacheControl ="";
}

CCacheControl::~CCacheControl()
{
	m_CacheControl ="";
}

void CCacheControl::setCacheControl(const string &CacheControl)
{
	m_CacheControl = CacheControl;
}

string CCacheControl::getCacheControl()
{
	return m_CacheControl;
}

