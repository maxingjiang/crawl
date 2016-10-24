/*
 * stringList.h
 *
 *  Created on: Jul 27, 2016
 *      Author: root
 */

#ifndef CRAWLSERVER_INCLUDE_STRINGLIST_H_
#define CRAWLSERVER_INCLUDE_STRINGLIST_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CstringList
{
public:
	CstringList();
	~CstringList();
public:
	vector<string> m_CstringList;
};

#endif /* CRAWLSERVER_INCLUDE_STRINGLIST_H_ */
