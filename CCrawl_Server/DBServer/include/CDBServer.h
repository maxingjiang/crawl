/*
 * CDBServer.h
 *
 *  Created on: Jul 21, 2016
 *      Author: root
 */

#ifndef INCLUDE_CRAWLDBSERVER_H_
#define INCLUDE_CRAWLDBSERVER_H_

#include "MysqlService.h"
#include <vector>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "common.h"

using namespace std;

class CDBServer
{
public:
	CDBServer();
	virtual ~CDBServer();

	void initMysqlPool(const string &host, const string &user, const string &pass, const string &dbname, int poolSize);
	void destroyMysqlPool();
	Connection* getConnection();
	int releaseConnection();

	//operate headers table
	vector< vector<string> > SelectMysql(int headersid, const string &domain);
	int deleteMysql(int headersid, const string &domain);
	int updateMysql(int headersid, const string &domain, const string &headersKey, const string &headersValue);

	//operate proxy table
	vector< vector<string> > SelectMysql_proxy(int columnnum);
	int deleteMysql_proxy(const string &proxyip, int proxyport);
	int updateMysql_proxy(const string &proxyip, int proxyport);

	//operate cookies table
	vector< vector<string> > SelectMysql_cookies(int cookieid, const string &website);
	int deleteMysql_cookies(int cookieid, const string &website);
	int updateMysql_cookies(int cookieid, const string &website, const string &cookieKey, const string &cookieValue, const string &domain,
			const string &path, const string &sendUseage, int isHttpOnly, const string &created, const string &deadline);

	vector<string> SelectMysql_cookies(int cookieid);
	vector<string> SelectMysql_cookies();


private:
	Connection* m_conn;
	vector< vector<string> > m_selectHeaders;
};

#endif /* INCLUDE_CRAWLDBSERVER_H_ */
