/*
 * insertRequestHeadersData.h
 *
 *  Created on: Jul 21, 2016
 *      Author: root
 */

#ifndef CRAWLSERVER_INCLUDE_INSERTREQUESTHEADERSDATA_H_
#define CRAWLSERVER_INCLUDE_INSERTREQUESTHEADERSDATA_H_

#include "CDBServer.h"
#include "readFile.h"
#include "split.h"

class CinsertRequestHeadersData
{
public:
	void insert_default_data();
	void insert_tianya_data();
	void insert_douban_data();
	void insert_csdn_data();
	void insert_weibo_data();
	void insert_zhihu_data();

	void insert_proxy_data();

	void insert_requestHeaders_to_db_from_file(const string &file);

public:
	CDBServer m_dbcrawl;
};


#endif /* CRAWLSERVER_INCLUDE_INSERTREQUESTHEADERSDATA_H_ */
