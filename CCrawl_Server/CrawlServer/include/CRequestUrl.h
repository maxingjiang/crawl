/*
 * CRequestUrl.h
 *
 *  Created on: Jul 26, 2016
 *      Author: root
 */

#ifndef CRAWLSERVER_INCLUDE_CREQUESTURL_H_
#define CRAWLSERVER_INCLUDE_CREQUESTURL_H_

#include <iostream>
#include <string>

using namespace std;

class CRequestUrl
{
public:
	CRequestUrl();
	~CRequestUrl();

    void setCRequestUrl(const string &url);
    string getCRequestUrl();
    void setFilename(const string &filename);
    string getFilename();
private:
	string m_url;
	string m_filename;
};

#endif /* CRAWLSERVER_INCLUDE_CREQUESTURL_H_ */
