
#ifndef INCLUDE_GETDATAFROMURL_H_
#define INCLUDE_GETDATAFROMURL_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include "readrequest.h"
#include "crawl.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include "getProxy.h"
#include "businfo.h"

using namespace std;
using std::string;

class CgetDataFromUrl
{
public:
    string getBusInfoByUrl(CURL *curl, string &Url, string &ip, int port, bool setproxy);

	int writebuslineToConf();

	vector<Cip_port> getUsfulProxyIP(vector<Cip_port> proxyips);

	int testProxyip(string ip, int port);

	void getAllUsefulProxyIP();

	int main1(int argc, char *argv[]);

};
#endif /* INCLUDE_GETDATAFROMURL_H_ */
