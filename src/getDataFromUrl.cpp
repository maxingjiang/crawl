
#include <iostream>
#include "getDataFromUrl.h"
#include "threadpool.h"

string CgetDataFromUrl::getBusInfoByUrl(CURL *curl, string &Url, string &ip, int port, bool setproxy)
{
	Ccrawl cr;

    curl=curl_easy_init();
    struct curl_slist *headers = NULL;
    std::string filename = "conf/request.conf";
    CreadConf rd;
    vector<string> header = rd.readrequest(filename);
    std::vector<std::string>::iterator iter = header.begin();
    //cout<<"request header===>: \n";
    for(; iter != header.end(); iter++)
    {
        //cout<<*iter<<endl;
        headers = curl_slist_append(headers, (*iter).c_str());
    }
    /*
    filename = "conf/cookie.conf";
    readConf rd1(filename);
    rd1.readrequest();
    std::vector<std::string>::iterator itercookie = rd1.m_requestconf.begin();
    //cout<<"cookie header===>: \n";
    std::string cookies = "Cookie: ";
    for(; itercookie != rd1.m_requestconf.end(); itercookie++)
    {
        //cout<<*itercookie<<endl;
        cookies = cookies + *itercookie;
    }
    //cout<<"cookie header end===>: \n";
    headers = curl_slist_append(headers, cookies.c_str());
	*/
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    if(setproxy == true)
    {
        curl_easy_setopt(curl, CURLOPT_PROXY, ip.c_str());
        curl_easy_setopt(curl, CURLOPT_PROXYPORT, port);
    }
    curl_easy_setopt(curl, CURLOPT_URL, Url.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1L);
    char buffer_data[1000000] = {0x0};
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Ccrawl::write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer_data);
    char buffer_header[10000] = {0x0};
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, Ccrawl::header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, buffer_header);
    //curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    //std::cout<<"header===>\n"<<buffer_header<<std::endl;
    //std::cout<<"body===>\n"<<buffer_data<<std::endl;
    return buffer_data;
}

int CgetDataFromUrl::writebuslineToConf()
{
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl;
	string url = "http://222.85.139.244:1001/BusService/Require_AllRouteData/?TimeStamp=1";
	Cbusinfo bus;
	int urlrequest = 0;
	int urlline = 0;
	time_t tt = time(NULL);
 	tm* t1= localtime(&tt);
 	char time1[100];
 	sprintf(time1, "%d-%02d-%02d %02d:%02d:%02d\n", t1->tm_year + 1900,t1->tm_mon + 1,t1->tm_mday,t1->tm_hour,t1->tm_min,t1->tm_sec);
 	string ip = "";
	string buslines_src = getBusInfoByUrl(curl, url, ip, 0, false);
	vector<CBusAllLine> buslines = bus.getAllLineInfo(buslines_src);
	std::vector<CBusAllLine>::iterator iter = buslines.begin();
	FILE *pbusline;
	if ((pbusline = fopen("conf/busline.conf", "w")) == NULL)
	    return 0;
	for(; iter != buslines.end(); iter++)
	{
		url = "http://222.85.139.244:1001/BusService/Require_RouteStatData/?RouteID="+iter->m_lineID;
		urlline++;
		buslines_src = getBusInfoByUrl(curl, url, ip, 0, false);
		vector<CBusTerminus> busStations = bus.getBusTerminus(pbusline, buslines_src);

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

vector<Cip_port> CgetDataFromUrl::getUsfulProxyIP(vector<Cip_port> proxyips)
{
	vector<Cip_port> proxys;
	vector<Cip_port>::iterator iter = proxyips.begin();
	char cmdsrc[] = "echo > proxy.txt";
	system(cmdsrc);
    for(; iter != proxyips.end(); iter++)
    {
    	int num = testProxyip(iter->m_ip, iter->m_port);
    	if(num == 1)
    	{
    		Cip_port proxy;
    		proxy.m_ip = iter->m_ip;
    		proxy.m_port = iter->m_port;
    		proxys.push_back(proxy);
    		char portsrc[10] = {0x0};
    		sprintf(portsrc, "%d", iter->m_port);
    		string cmd = "echo "+iter->m_ip+":"+string(portsrc)+" >> proxy.txt";
    		system(cmd.c_str());
    	}
    	//sleep(1);
    }
    return proxys;
}

int CgetDataFromUrl::testProxyip(string ip, int port)
{
    CURL *curl;
    CURLcode res;
    Ccrawl cr;
    curl = curl_easy_init();
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_POST, 1L);
    	curl_easy_setopt(curl, CURLOPT_PROXY, ip.c_str());
    	curl_easy_setopt(curl, CURLOPT_PROXYPORT, port);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1L);
        struct curl_slist *headers = NULL;
        std::string filename = "conf/request.conf";
        CreadConf rd;
        vector<string> headdata = rd.readrequest(filename);
        std::vector<std::string>::iterator iter = headdata.begin();
        //cout<<"request header===>: \n";
        for(; iter != headdata.end(); iter++)
        {
            //cout<<*iter<<endl;
            headers = curl_slist_append(headers, (*iter).c_str());
        }
        //curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        //curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, "http://222.85.139.244:1001/BusService/Require_AllRouteData/?TimeStamp=1");
        char buffer_data[1000000] = {0x0};
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Ccrawl::write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer_data);
        char buffer_header[10000] = {0x0};
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, Ccrawl::header_callback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, buffer_header);
        res = curl_easy_perform(curl);
        //std::cout<<"buffer_data length===>\n"<<strlen(buffer_data)<<std::endl;
        curl_easy_cleanup(curl);
        int num = string(buffer_header).find("200 OK");
        std::cout<<ip<<":"<<port<<" num:"<<num<<std::endl;
        if( num >= 0)
        {
        	cout<<"<<======pass=========>>"<<ip<<":"<<port<<endl;
        	return 1;
        }
        else
        	return 0;
    }
    return 0;
}

void CgetDataFromUrl::getAllUsefulProxyIP()
{
	CProxyIP ip;
	vector<Cip_port> ips = ip.readProxy("a.txt");
	CgetDataFromUrl proxy;
	proxy.getUsfulProxyIP(ips);
}

int CgetDataFromUrl::main1(int argc, char *argv[])
{
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl;
	string url = "http://222.85.139.244:1001/BusService/Require_AllRouteData/?TimeStamp=1";
	Cbusinfo bus;
	int urlrequest = 0;
	int urlline = 0;
	time_t tt = time(NULL);
 	tm* t1= localtime(&tt);
 	char time1[100];
 	sprintf(time1, "%d-%02d-%02d %02d:%02d:%02d\n", t1->tm_year + 1900,t1->tm_mon + 1,t1->tm_mday,t1->tm_hour,t1->tm_min,t1->tm_sec);
 	string ip = "";
 	string buslines_src = getBusInfoByUrl(curl, url, ip, 0, false);
	vector<CBusAllLine> buslines = bus.getAllLineInfo(buslines_src);
	std::vector<CBusAllLine>::iterator iter = buslines.begin();
	    //cout<<"request header===>: \n";
	for(; iter != buslines.end(); iter++)
	{
		url = "http://222.85.139.244:1001/BusService/Require_RouteStatData/?RouteID="+iter->m_lineID;
		urlline++;
		buslines_src = getBusInfoByUrl(curl, url, ip, 0, false);
		vector<CBusTerminus> busStations = bus.getBusTerminus(NULL,buslines_src);
		std::vector<CBusTerminus>::iterator iter1 = busStations.begin();
		for(; iter1 != busStations.end(); iter1++)
		{
			url = "http://222.85.139.244:1001/BusService/QueryDetail_ByRouteID/?RouteID="+iter1->m_lineID+"&SegmentID="+iter1->m_terminusId;
			urlrequest++;
			cout<<"<*****url*****>"<<url<<endl;
			buslines_src = getBusInfoByUrl(curl, url, ip, 0, false);
			vector<CBusPositionInfo> busPositionInfos = bus.getBusPositonInfo(*iter1, buslines_src);
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

