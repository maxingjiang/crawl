/*
 * crawlstruct.h
 *
 *  Created on: Jun 8, 2016
 *      Author: root
 */

#ifndef INCLUDE_CRAWLSTRUCT_H_
#define INCLUDE_CRAWLSTRUCT_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <curl/curl.h>
#include <curl/easy.h>
#include "gumbo/gumbo.h"

using namespace std;

class CCrawlStruct
{
public:
	void init(string url, int urlnum, string keyword);
	void clear();
	void getUsefulUrl();
	void getAllProxyIp(string &dataword);

	void getUrlLink(string &keyword, string &urldata);

	void search_for_links(GumboNode* node);

	void writeProxyToFile(string pathfile);

public:
	CURL *m_curl;
	string m_keyword;
	unsigned int m_url_index;
	unsigned int m_url_nums;
	vector <string> m_allurl;
	vector <string> m_allproxyip;
	vector <string> m_usefulurls;

};

#endif /* INCLUDE_CRAWLSTRUCT_H_ */
