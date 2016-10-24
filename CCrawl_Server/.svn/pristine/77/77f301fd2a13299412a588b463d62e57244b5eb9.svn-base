
#ifndef INCLUDE_CRESPONSEBODY_H_
#define INCLUDE_CRESPONSEBODY_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "Proxy.h"

using namespace std;
using std::string;

class CResponseBody
{
public:
	CResponseBody();
	virtual ~CResponseBody();
	//set request headers and postpameres, if postmeres is empty, not post mode
	string getUrlData(const string &url, const vector<string> &headersparames, const string &postParames,
			const string &ip, int port, bool setproxy);
	string getResponseHeader();
	string getResponseBody();

private:
	string m_url; //current url
	string m_responseHeader;
	string m_responseBody;

};
#endif /* INCLUDE_CRESPONSEBODY_H_ */
