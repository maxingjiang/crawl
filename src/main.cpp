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

int run()
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
    ifstream fin("conf/busline.conf");
    while( fin.getline(str,LINE_LENGTH) != NULL)
    {
        //std::cout << "Read from file: " << str << std::endl;
    	std::vector<std::string> buslineinfo = cr.split(str, "---");
    	url = "http://222.85.139.244:1001/BusService/QueryDetail_ByRouteID/?RouteID="+buslineinfo[0]+"&SegmentID="+buslineinfo[2];
    	urlrequest++;
    	cout<<"<*****url*****>"<<url<<endl;
    	buslines_src = getBusInfoByUrl(curl, url);
    	vector<busPositionInfo> busPositionInfos = bus.getBusPositonInfo(*iter1, buslines_src);
    }

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
