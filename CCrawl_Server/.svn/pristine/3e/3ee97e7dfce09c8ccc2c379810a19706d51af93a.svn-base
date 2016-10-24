/*
 * CProxyManager.cpp
 *
 *  Created on: Aug 12, 2016
 *      Author: root
 */

#include "CProxyManager.h"

unsigned int CProxyManager::proxy_index = 0;

CProxyManager::CProxyManager()
{
	m_proxymanagers.clear();
}

CProxyManager::~CProxyManager()
{
	m_proxymanagers.clear();
}

int CProxyManager::getProxy(CProxy &proxy)
{
	if(m_proxymanagers.size() == 0)
	{
		return 0;
	}
	if(CProxyManager::proxy_index == m_proxymanagers.size())
	{
		CProxyManager::proxy_index = 0;
	}
	proxy = m_proxymanagers[CProxyManager::proxy_index];
	CProxyManager::proxy_index++;
	return 1;
}

int CProxyManager::getProxyFromDB(CDBServer *conn, int columnnum)
{
	if(conn == NULL)
	{
		cout<<__FILE__<<":"<<__LINE__<<", conn is NULL"<<endl;
		return 0;
	}
	Connection *connect = conn->getConnection();
	if(!connect)
	{
		cout <<__FILE__<<__LINE__<< "getConnection NULL pointer" << endl;
		return -1;
	}
	vector< vector<string> > mysqldata = conn->SelectMysql_proxy(columnnum);
	conn->releaseConnection();

	int row = mysqldata.size();
	for(int rownum = 0; rownum < row; rownum++)
	{
		int column = mysqldata[rownum].size();
		if(column < 3)
		{
			return row;
		}
		if(mysqldata[rownum][1].size() > 0 && mysqldata[rownum][2].size() > 0)
		{
			CProxy localproxy;
			localproxy.setProxy(mysqldata[rownum][1], atoi(mysqldata[rownum][2].c_str()));
			m_proxymanagers.push_back(localproxy);
		}
	}
	return row;
}
