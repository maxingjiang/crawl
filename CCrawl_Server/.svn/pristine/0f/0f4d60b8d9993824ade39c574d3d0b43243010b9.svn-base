/*
 * CDBServer.cpp
 *
 *  Created on: Jul 21, 2016
 *      Author: root
 */

#include "CDBServer.h"

CDBServer::CDBServer()
{
	m_conn = NULL;
	m_selectHeaders.clear();
}

CDBServer::~CDBServer()
{
	m_selectHeaders.clear();
}

void CDBServer::initMysqlPool(const string &host, const string &user, const string &pass, const string &dbname, int poolSize)
{
	Pool::initPool(host,user,pass,dbname,poolSize);
}

void CDBServer::destroyMysqlPool()
{
	 Pool::destroyPool();
}

Connection* CDBServer::getConnection()
{
	m_conn = Pool::getConnection();
	return m_conn;
}

int CDBServer::releaseConnection()
{
	return Pool::releaseConnection(m_conn);
}

vector< vector<string> > CDBServer::SelectMysql(int headersid, const string &domain)
{
	char sql[CRAWLDB_DB_SQL_LENGTH] = "";
	sprintf(sql, "SELECT * FROM `%s` WHERE `%s` = '%s' and `%s` = %d;", CRAWLDB_TABLE_headers, CRAWLDB_headers_domain, domain.c_str(),
			CRAWLDB_headers_ID, headersid);
	string query = sql;
	QueryResult queryResult = m_conn->executeSelectQuery(query);

	int row = queryResult.getRowCount();
	if(row == 0) //select is empty
	{
		return m_selectHeaders;
	}
	int column = queryResult.getColumnCount();
	for(int rownum = 0; rownum < row; rownum++)
	{
		vector<string> columndata;
		columndata.clear();
		for(int columnnum = 0; columnnum < column; columnnum++)
		{
			columndata.push_back(queryResult.getElement(rownum, columnnum));
			//cout << queryResult.getElement(rownum, columnnum) << ", ";
		}
		//cout<<endl;
		m_selectHeaders.push_back(columndata);
	}
	return m_selectHeaders;
}
int CDBServer::deleteMysql(int headersid, const string &domain)
{
	char sql[CRAWLDB_DB_SQL_LENGTH] = "";
	sprintf(sql, "DELETE FROM `%s` WHERE `%s` = '%s' and `%s` = %d;", CRAWLDB_TABLE_headers, CRAWLDB_headers_domain, domain.c_str(),
			CRAWLDB_headers_ID, headersid);
	string query = sql;
	//cout<<query<<endl;
	int status = m_conn->executeReplaceQuery(query);
	return status;
}

int CDBServer::updateMysql(int headersid, const string &domain, const string &headersKey, const string &headersValue)
{
	char sql[CRAWLDB_DB_SQL_LENGTH] = "";
	sprintf(sql, "REPLACE INTO `%s` (`%s`, `%s`, `%s`, `%s`) VALUES ('%d', '%s', '%s', '%s');",
			CRAWLDB_TABLE_headers, CRAWLDB_headers_ID, CRAWLDB_headers_domain, CRAWLDB_headers_KEY, CRAWLDB_headers_VALUE,
			headersid, domain.c_str(), headersKey.c_str(), headersValue.c_str());
	string query = sql;
	int status = m_conn->executeReplaceQuery(query);
	return status;
}

vector< vector<string> > CDBServer::SelectMysql_proxy(int columnnum)
{
	char sql[CRAWLDB_DB_SQL_LENGTH] = "";
	sprintf(sql, "SELECT * FROM `%s` LIMIT %d;", CRAWLDB_TABLE_PROXY, columnnum);
	string query = sql;
	QueryResult queryResult = m_conn->executeSelectQuery(query);

	int row = queryResult.getRowCount();
	if(row == 0) //select is empty
	{
		return m_selectHeaders;
	}
	int column = queryResult.getColumnCount();
	for(int rownum = 0; rownum < row; rownum++)
	{
		vector<string> columndata;
		columndata.clear();
		for(int columnnum = 0; columnnum < column; columnnum++)
		{
			columndata.push_back(queryResult.getElement(rownum, columnnum));
			//cout << queryResult.getElement(rownum, columnnum) << ", ";
		}
		//cout<<endl;
		m_selectHeaders.push_back(columndata);
	}
	return m_selectHeaders;
}

int CDBServer::deleteMysql_proxy(const string &proxyip, int proxyport)
{
	char sql[CRAWLDB_DB_SQL_LENGTH] = "";
	sprintf(sql, "DELETE FROM `%s` WHERE `%s` = '%s' and `%s` = %d;", CRAWLDB_TABLE_PROXY, CRAWLDB_PROXY_IP, proxyip.c_str()
			, CRAWLDB_PROXY_PORT, proxyport);
	string query = sql;
	//cout<<query<<endl;
	int status = m_conn->executeReplaceQuery(query);
	return status;
}

int CDBServer::updateMysql_proxy(const string &proxyip, int proxyport)
{
	char sql[CRAWLDB_DB_SQL_LENGTH] = "";
	sprintf(sql, "REPLACE INTO `%s` (`%s`, `%s`) VALUES ('%s', '%d');",
			CRAWLDB_TABLE_PROXY, CRAWLDB_PROXY_IP, CRAWLDB_PROXY_PORT, proxyip.c_str(), proxyport);
	string query = sql;
	int status = m_conn->executeReplaceQuery(query);
	return status;
}

vector< vector<string> > CDBServer::SelectMysql_cookies(int cookieid, const string &website)
{
	char sql[CRAWLDB_DB_SQL_LENGTH] = "";
	sprintf(sql, "SELECT * FROM `%s` WHERE `%s` = '%d' and `%s` = '%s';", CRAWLDB_TABLE_cookies, CRAWLDB_cookies_cookieid, cookieid, CRAWLDB_cookies_website, website.c_str());
	string query = sql;
	QueryResult queryResult = m_conn->executeSelectQuery(query);

	int row = queryResult.getRowCount();
	if(row == 0) //select is empty
	{
		return m_selectHeaders;
	}
	int column = queryResult.getColumnCount();
	for(int rownum = 0; rownum < row; rownum++)
	{
		vector<string> columndata;
		columndata.clear();
		for(int columnnum = 0; columnnum < column; columnnum++)
		{
			columndata.push_back(queryResult.getElement(rownum, columnnum));
			//cout << queryResult.getElement(rownum, columnnum) << ", ";
		}
		//cout<<endl;
		m_selectHeaders.push_back(columndata);
	}
	return m_selectHeaders;
}

int CDBServer::deleteMysql_cookies(int cookieid, const string &website)
{
	char sql[CRAWLDB_DB_SQL_LENGTH] = "";
	sprintf(sql, "DELETE FROM `%s` WHERE `%s` = '%d' and `%s` = '%s';", CRAWLDB_TABLE_cookies, CRAWLDB_cookies_cookieid, cookieid, CRAWLDB_cookies_website, website.c_str());
	string query = sql;
	//cout<<query<<endl;
	int status = m_conn->executeReplaceQuery(query);
	return status;
}

int CDBServer::updateMysql_cookies(int cookieid, const string &website, const string &cookieKey, const string &cookieValue, const string &domain, const string &path,
		const string &sendUseage, int isHttpOnly, const string &created, const string &deadline)
{
	char sql[CRAWLDB_DB_SQL_LENGTH] = "";
	sprintf(sql, "REPLACE INTO `%s` (`%s`, `%s`, `%s`, `%s`, `%s`, `%s`, `%s`, `%s`, `%s`, `%s`) VALUES ('%d', '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%s', '%s');",
			CRAWLDB_TABLE_cookies, CRAWLDB_cookies_cookieid, CRAWLDB_cookies_website, CRAWLDB_cookies_cookieKey, CRAWLDB_cookies_cookieValue, CRAWLDB_cookies_domain, CRAWLDB_cookies_path,
			CRAWLDB_cookies_sendUseage, CRAWLDB_cookies_isHttpOnly, CRAWLDB_cookies_created, CRAWLDB_cookies_deadline,
			cookieid, website.c_str(), cookieKey.c_str(), cookieValue.c_str(), domain.c_str(), path.c_str(), sendUseage.c_str(), isHttpOnly, created.c_str(), deadline.c_str());
	string query = sql;
	int status = m_conn->executeReplaceQuery(query);
	return status;
}

vector<string> CDBServer::SelectMysql_cookies(int cookieid)
{
	vector<string> cookieids;
	char sql[CRAWLDB_DB_SQL_LENGTH] = "";
	sprintf(sql, "SELECT website FROM `%s` WHERE `%s` = '%d';", CRAWLDB_TABLE_cookies, CRAWLDB_cookies_cookieid, cookieid);
	string query = sql;
	QueryResult queryResult = m_conn->executeSelectQuery(query);

	int row = queryResult.getRowCount();
	if(row == 0) //select is empty
	{
		return cookieids;
	}
	//int column = queryResult.getColumnCount();

	for(int rownum = 0; rownum < row; rownum++)
	{
		cookieids.push_back(queryResult.getElement(rownum, 0));
	}
	return cookieids;
}

vector<string> CDBServer::SelectMysql_cookies()
{
	vector<string> cookieids;
	char sql[CRAWLDB_DB_SQL_LENGTH] = "";
	sprintf(sql, "SELECT cookieid FROM `%s`;", CRAWLDB_TABLE_cookies);
	string query = sql;
	QueryResult queryResult = m_conn->executeSelectQuery(query);

	int row = queryResult.getRowCount();
	if(row == 0) //select is empty
	{
		return cookieids;
	}
	//int column = queryResult.getColumnCount();

	for(int rownum = 0; rownum < row; rownum++)
	{
		cookieids.push_back(queryResult.getElement(rownum, 0));
	}
	return cookieids;
}


