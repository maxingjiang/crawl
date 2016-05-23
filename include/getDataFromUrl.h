
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

using namespace :: std;
using std::string;

string getBusInfoByUrl(CURL *curl, string &Url, string &ip, int port, bool setproxy);

int writebuslineToConf();

vector<ip_port> getUsfulProxyIP(vector<ip_port> proxyips);

int testProxyip(string ip, int port);

int main1(int argc, char *argv[]);

#endif /* INCLUDE_GETDATAFROMURL_H_ */