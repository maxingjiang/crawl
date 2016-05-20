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


void* run(void *arg)
{
	threadArgs *threadargs = (threadArgs *)arg;
	string url = "http://222.85.139.244:1001/BusService/QueryDetail_ByRouteID/?RouteID="
			+threadargs->busterminus.lineID+"&SegmentID="+threadargs->busterminus.terminusId;
	cout<<"<*****url*****>"<<url<<" "<<threadargs->ip<<":"<<threadargs->port<<endl;
	string buslines_src;
	//buslines_src = getBusInfoByUrl(threadargs->curl, url, threadargs->ip, threadargs->port, true); //set proxy
	//if(buslines_src.length() <= 0)
	buslines_src = getBusInfoByUrl(threadargs->curl, url, threadargs->ip, threadargs->port, false); //not set proxy
	//cout<<"<*****buslines_src*****>"<<buslines_src<<endl;
	businfo bus;
	vector<busPositionInfo> busPositionInfos = bus.getBusPositonInfo(threadargs->busterminus, buslines_src);
}

int run1()
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl;
    businfo bus;
    const int LINE_LENGTH = 2048;
    char str[LINE_LENGTH];
    crawl cr;
    string url, buslines_src;
    int urlrequest = 0;
    cr.clear();
    vector<threadArgs> threadargss;
    ifstream fin("conf/busline.conf");
    time_t tt = time(NULL);
    tm* t1= localtime(&tt);
    char time1[100];
    sprintf(time1, "%d-%02d-%02d %02d:%02d:%02d\n", t1->tm_year + 1900,t1->tm_mon + 1,t1->tm_mday,t1->tm_hour,t1->tm_min,t1->tm_sec);

    ProxyIP ip("conf/proxy.conf");
    vector<ip_port> ips = ip.readProxy();
    int ips_length = ips.size();
    int ipnum = 0;
    while( fin.getline(str,LINE_LENGTH) != NULL)
    {
        //std::cout << "Read from file: " << str << std::endl;
    	std::vector<std::string> buslineinfo = cr.split(str, "---");
    	threadArgs threadargs;
    	threadargs.curl = curl;
    	threadargs.ip = ips[ipnum].ip;
    	threadargs.port = ips[ipnum].port;
    	threadargs.busterminus.lineID = buslineinfo[0];
    	threadargs.busterminus.lineName = buslineinfo[1];
    	threadargs.busterminus.terminusId = buslineinfo[2];
    	threadargs.busterminus.terminusName = buslineinfo[3];
    	threadargss.push_back(threadargs);
    	ipnum++;
    	if(ipnum >= ips_length)
    		ipnum = 0;
    	urlrequest++;
    }
    int urllines = threadargss.size();
    cout<<"urllines===>"<<urllines<<endl;
    pool_init (5);
    for (int i = 0; i < urllines; i++) {
        pool_add_worker (run, &threadargss[i]);
    }
    sleep(2);
    while(1)
    {
    	if(pool->cur_queue_size == 0)
    	{
    		cout<<"===========exit\n";
    		pool_destroy ();
    		break;
    	}
    	continue;
    }
    cout<<"urlrequestnum===>"<<urlrequest<<endl;
    time_t tt1 = time(NULL);
    tm* t2= localtime(&tt1);
    char time2[100];
    sprintf(time2, "%d-%02d-%02d %02d:%02d:%02d\n", t2->tm_year + 1900,t2->tm_mon + 1,t2->tm_mday,t2->tm_hour,t2->tm_min,t2->tm_sec);
    cout<<time1;
    cout<<time2;
    curl_global_cleanup();
    return 0;
}


int main(int argc, char *argv[])
{
	run1();
	/*
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl;
	string url = "http://222.85.139.244:1001/BusService/Require_AllRouteData/?TimeStamp=1";
	testgetBusInfoByUrl(curl, url);
	*/
	//postUrl();
	//ProxyIP ip("conf/proxy.conf");
	//vector<ip_port> ips = ip.readProxy();
	//getUsfulProxyIP(ips);

	exit(0);
}

