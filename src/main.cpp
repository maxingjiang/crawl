#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include "readrequest.h"
#include "crawl.h"
#include "test.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <vector>
#include "businfo.h"
#include "getDataFromUrl.h"
#include <time.h>
#include "threadpool.h"
#include "getProxy.h"

using namespace std;

/*
int main(int argc, char *argv[])
{
	start();

	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl;
	string url = "http://222.85.139.244:1001/BusService/Require_AllRouteData/?TimeStamp=1";
	testgetBusInfoByUrl(curl, url);

	//postUrl();
	//ProxyIP ip("conf/proxy.conf");
	//vector<ip_port> ips = ip.readProxy();
	//getUsfulProxyIP(ips);

	exit(0);
}
*/
