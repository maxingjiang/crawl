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

using namespace std;

int main1(int argc, char *argv[])
{
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl;
	string url = "http://222.85.139.244:1001/BusService/Require_AllRouteData/?TimeStamp=1";
	businfo bus;
	int urlrequest = 0;
	int urlline = 0;
	time_t tt = time(NULL);
 	tm* t1= localtime(&tt);
 	char time1[100];
 	sprintf(time1, "%d-%02d-%02d %02d:%02d:%02d\n", t1->tm_year + 1900,t1->tm_mon + 1,t1->tm_mday,t1->tm_hour,t1->tm_min,t1->tm_sec);
	string buslines_src = getBusInfoByUrl(curl, url);
	vector<busAllLine> buslines = bus.getAllLineInfo(buslines_src);
	std::vector<busAllLine>::iterator iter = buslines.begin();
	    //cout<<"request header===>: \n";
	for(; iter != buslines.end(); iter++)
	{
		url = "http://222.85.139.244:1001/BusService/Require_RouteStatData/?RouteID="+iter->lineID;
		urlline++;
		buslines_src = getBusInfoByUrl(curl, url);
		vector<busTerminus> busStations = bus.getBusTerminus(NULL,buslines_src);
		std::vector<busTerminus>::iterator iter1 = busStations.begin();
		for(; iter1 != busStations.end(); iter1++)
		{
			url = "http://222.85.139.244:1001/BusService/QueryDetail_ByRouteID/?RouteID="+iter1->lineID+"&SegmentID="+iter1->terminusId;
			urlrequest++;
			cout<<"<*****url*****>"<<url<<endl;
			buslines_src = getBusInfoByUrl(curl, url);
			vector<busPositionInfo> busPositionInfos = bus.getBusPositonInfo(*iter1, buslines_src);
		}
	}
	time_t tt1 = time(NULL);
 	tm* t2= localtime(&tt1);
 	char time2[100];
 	sprintf(time2, "%d-%02d-%02d %02d:%02d:%02d\n", t2->tm_year + 1900,t2->tm_mon + 1,t2->tm_mday,t2->tm_hour,t2->tm_min,t2->tm_sec);
 	cout<<time1;
 	cout<<time2;
 	cout<<"urlrlinenum===>"<<urlline<<endl;
 	cout<<"urlrequestnum===>"<<urlrequest<<endl;

    exit(0);
}

void* run(void *arg)
{
	threadArgs *threadargs = (threadArgs *)arg;
	string url = "http://222.85.139.244:1001/BusService/QueryDetail_ByRouteID/?RouteID="
			+threadargs->busterminus.lineID+"&SegmentID="+threadargs->busterminus.terminusId;
	//cout<<"<*****url*****>"<<url<<endl;
	string buslines_src = getBusInfoByUrl(threadargs->curl, url);
	//string buslines_src= "{\"RouteID\":253,\"SegmentID\":9190,\"BusPosList\":[{\"BusID\":\"907408\",\"BusName\":\"907408\",\"StationID\":\"3518\",\"ArriveTime\":\"2016-05-18 09:11:24\",\"ArriveStaInfo\":\"111\",\"NextStaInfo\":\"222\",\"BusPostion\":{\"Longitude\":106.77839,\"Latitude\":26.66012}},{\"BusID\":\"907410\",\"BusName\":\"907410\",\"StationID\":\"9\",\"ArriveTime\":\"2016-05-18 09:11:36\",\"ArriveStaInfo\":\"333\",\"NextStaInfo\":\"444\",\"BusPostion\":{\"Longitude\":106.70674,\"Latitude\":26.56263}}]}";
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

    while( fin.getline(str,LINE_LENGTH) != NULL)
    {
        //std::cout << "Read from file: " << str << std::endl;
    	std::vector<std::string> buslineinfo = cr.split(str, "---");
    	threadArgs threadargs;
    	threadargs.curl = curl;
    	threadargs.busterminus.lineID = buslineinfo[0];
    	threadargs.busterminus.lineName = buslineinfo[1];
    	threadargs.busterminus.terminusId = buslineinfo[2];
    	threadargs.busterminus.terminusName = buslineinfo[3];
    	threadargss.push_back(threadargs);
    	urlrequest++;
    }
    int urllines = threadargss.size();
    pool_init (5);
    for (int i = 0; i < urllines; i++) {
        pool_add_worker (run, &threadargss[i]);
    }
    sleep (1);
    pool_destroy ();

    cout<<"urlrequestnum===>"<<urlrequest<<endl;
    time_t tt1 = time(NULL);
    tm* t2= localtime(&tt1);
    char time2[100];
    sprintf(time2, "%d-%02d-%02d %02d:%02d:%02d\n", t2->tm_year + 1900,t2->tm_mon + 1,t2->tm_mday,t2->tm_hour,t2->tm_min,t2->tm_sec);
    cout<<time1;
    cout<<time2;
    return 0;
}

int writebusline()
{
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl;
	string url = "http://222.85.139.244:1001/BusService/Require_AllRouteData/?TimeStamp=1";
	businfo bus;
	int urlrequest = 0;
	int urlline = 0;
	time_t tt = time(NULL);
 	tm* t1= localtime(&tt);
 	char time1[100];
 	sprintf(time1, "%d-%02d-%02d %02d:%02d:%02d\n", t1->tm_year + 1900,t1->tm_mon + 1,t1->tm_mday,t1->tm_hour,t1->tm_min,t1->tm_sec);

	string buslines_src = getBusInfoByUrl(curl, url);
	vector<busAllLine> buslines = bus.getAllLineInfo(buslines_src);
	std::vector<busAllLine>::iterator iter = buslines.begin();
	FILE *pbusline;
	if ((pbusline = fopen("conf/busline.conf", "w")) == NULL)
	    return 0;
	for(; iter != buslines.end(); iter++)
	{
		url = "http://222.85.139.244:1001/BusService/Require_RouteStatData/?RouteID="+iter->lineID;
		urlline++;
		buslines_src = getBusInfoByUrl(curl, url);
		vector<busTerminus> busStations = bus.getBusTerminus(pbusline, buslines_src);

	}
	fclose(pbusline);
	time_t tt1 = time(NULL);
 	tm* t2= localtime(&tt1);
 	char time2[100];
 	sprintf(time2, "%d-%02d-%02d %02d:%02d:%02d\n", t2->tm_year + 1900,t2->tm_mon + 1,t2->tm_mday,t2->tm_hour,t2->tm_min,t2->tm_sec);
 	cout<<time1;
 	cout<<time2;
 	cout<<"urlrlinenum===>"<<urlline<<endl;
 	cout<<"urlrequestnum===>"<<urlrequest<<endl;

    return 0;
}

int main(int argc, char *argv[])
{
	run1();
	exit(0);
}

