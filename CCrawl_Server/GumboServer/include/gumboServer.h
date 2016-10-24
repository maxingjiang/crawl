/*
 * gumboServer.h
 *
 *  Created on: Jul 5, 2016
 *      Author: root
 */

#ifndef GUMBOSERVER_INCLUDE_GUMBOSERVER_H_
#define GUMBOSERVER_INCLUDE_GUMBOSERVER_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sys/stat.h>
#include <gumbo.h>
#include "readFile.h"
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class CRuleArgs
{
public:
	CRuleArgs();
	~CRuleArgs();
public:
	GumboTag m_tag;
	string m_attributes;
	string m_value;
	string m_text;
};

class CgumboServer
{
public:
	vector<string> getUrlLink(string &responsedata, string &keyword);
	void search_for_links(GumboNode* node, string &keyword, vector<string> &links);

	void print_info(GumboNode *node, GumboAttribute *attr);
	void get_info(GumboNode *node, vector<CRuleArgs> &deepRule, unsigned int num);
	void getAllInfo(string &responsedata);

	vector<CRuleArgs> getRuleArgs(string rulefile);
	GumboTag getTag(const string &strtag);
	void ReplaceStr(string &strContent,const string &strSrc,const string &strDest,bool ignoreCase);
};

#endif /* GUMBOSERVER_INCLUDE_GUMBOSERVER_H_ */
