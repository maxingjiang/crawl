/*
 * CProxyManager.h
 *
 *  Created on: Aug 12, 2016
 *      Author: root
 */

#ifndef CRAWLSERVER_INCLUDE_CPROXYMANAGER_H_
#define CRAWLSERVER_INCLUDE_CPROXYMANAGER_H_

#include <iostream>
#include <vector>
#include <string>
#include "CDBServer.h"
#include "Proxy.h"

using namespace std;

class CProxyManager
{
public:
	CProxyManager();
	virtual ~CProxyManager();

	int getProxy(CProxy &proxy);
	int getProxyFromDB(CDBServer *conn, int columnnum);

private:
	vector<CProxy> m_proxymanagers;
	static unsigned int proxy_index;
};

#endif /* CRAWLSERVER_INCLUDE_CPROXYMANAGER_H_ */
