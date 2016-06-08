/*
 * businfo.cpp
 *
 *  Created on: May 17, 2016
 *      Author: mxj
 */
#include <iostream>
#include "businfo.h"
#include<iomanip>
#include <sstream>
#include <pthread.h>
#include "crawl.h"
#include "getProxy.h"
#include "getDataFromUrl.h"
#include "threadpool.h"
#include "common.h"
#include <sys/file.h>

pthread_mutex_t BACK_COMM_mutex = PTHREAD_MUTEX_INITIALIZER ;


void Cbusinfo::clearInfo()
{
	m_bus.m_lineID = "";
	m_bus.m_lineName = "";
	m_bus.m_terminusId = "";
	m_bus.m_terminusName = "";
	m_bus.m_busId = "";
	m_bus.m_stationID = "";
	m_bus.m_stationName = "";
	m_bus.m_arriveTime = "";
	m_bus.m_arriveStaInfo = "";
	m_bus.m_nextStaInfo = "";
	m_bus.m_Latitude = 0.0;
	m_bus.m_Longitude = 0.0;
}

void Cbusinfo::setInfo(string lineID, string lineName, string terminusId, string terminusName,
				string busId, string stationID, string stationName, string arriveTime,
				string arriveStaInfo, string nextStaInfo, double Latitude, double Longitude)
{
	m_bus.m_lineID = lineID;
	m_bus.m_lineName = lineName;
	m_bus.m_terminusId = terminusId;
	m_bus.m_terminusName = terminusName;
	m_bus.m_busId = busId;
	m_bus.m_stationID = stationID;
	m_bus.m_stationName = stationName;
	m_bus.m_arriveTime = arriveTime;
	m_bus.m_arriveStaInfo = arriveStaInfo;
	m_bus.m_nextStaInfo = nextStaInfo;
	m_bus.m_Latitude = Latitude;
	m_bus.m_Longitude = Longitude;
}

vector<CBusAllLine> Cbusinfo::getAllLineInfo(string &src)
{
	Json::Reader reader;
	Json::Value value;
	vector<CBusAllLine> allline;
	allline.clear();

	if (reader.parse(src, value))
	{
		const Json::Value arrayNum = value["RouteList"];

		int file_size = arrayNum.size();
		for(int i = 0; i < file_size; ++i)
		{
			CBusAllLine line;
			string lineID = arrayNum[i]["RouteID"].asString();
			string lineName = arrayNum[i]["RouteName"].asString();
			line.m_lineID = lineID;
			line.m_lineName = lineName;
			//cout<<lineID<<": "<<lineName<<endl;
			allline.push_back(line);
		}
	}
	return allline;
}

vector<CBusStation> Cbusinfo::getBusStation(string &src)
{
	Json::Reader reader;
	Json::Value value;
	vector<CBusStation> busstation;
	busstation.clear();

	if (reader.parse(src, value))
	{
		int arrayNum = value.size();

		for(int i = 0; i < arrayNum; ++i)
		{
			CBusStation lineStationInfo;

			lineStationInfo.m_lineID = value[i]["RouteID"].asString();
			lineStationInfo.m_lineName = value[i]["RouteName"].asString();

			const Json::Value terminusList = value[i]["SegmentList"];
			int  terminusNum = terminusList.size();
			for(int terminus = 0; terminus < terminusNum; ++terminus)
			{
				lineStationInfo.m_terminusId = terminusList[terminus]["SegmentID"].asString();
				lineStationInfo.m_terminusName = terminusList[terminus]["SegmentName"].asString();

				const Json::Value stationList = terminusList[terminus]["StationList"];
				int  stationNum = stationList.size();
				for(int station = 0; station < stationNum; ++station)
				{
					lineStationInfo.m_stationID = stationList[station]["StationID"].asString();
					lineStationInfo.m_stationName = stationList[station]["StationName"].asString();
					lineStationInfo.m_stationPos.m_Latitude = stationList[station]["StationPostion"]["Latitude"].asDouble();
					lineStationInfo.m_stationPos.m_Longitude = stationList[station]["StationPostion"]["Longitude"].asDouble();
					/*cout<<lineStationInfo.m_lineID<<"=>"<<lineStationInfo.m_lineName<<"=>"<<lineStationInfo.m_terminusId
							<<"=>"<<lineStationInfo.m_terminusName<<"=>"<<lineStationInfo.m_stationID<<"=>"<<lineStationInfo.m_stationName
							<<"=>"<<lineStationInfo.m_stationPos.m_Latitude<<"=>"<<lineStationInfo.m_stationPos.m_Longitude<<endl;*/
					busstation.push_back(lineStationInfo);
				}
			}
		}
	}
	return busstation;
}

vector<CBusTerminus> Cbusinfo::getBusTerminus(string &src)
{
	Json::Reader reader;
	Json::Value value;
	vector<CBusTerminus> busterminuss;
	busterminuss.clear();

	if (reader.parse(src, value))
	{
		int arrayNum = value.size();

		for(int i = 0; i < arrayNum; ++i)
		{
			CBusTerminus busterminus;

			busterminus.m_lineID = value[i]["RouteID"].asString();
			busterminus.m_lineName = value[i]["RouteName"].asString();

			const Json::Value terminusList = value[i]["SegmentList"];
			int  terminusNum = terminusList.size();
			for(int terminus = 0; terminus < terminusNum; ++terminus)
			{
				busterminus.m_terminusId = terminusList[terminus]["SegmentID"].asString();
				busterminus.m_terminusName = terminusList[terminus]["SegmentName"].asString();
				string FirstTime = terminusList[terminus]["FirstTime"].asString();
				string LastTime = terminusList[terminus]["LastTime"].asString();
				Ccrawl cr;
				vector<string> localtime = cr.split(FirstTime, " ");
				string firsttime = localtime[1];
				localtime.clear();
				localtime = cr.split(LastTime, " ");
				string lasttime = localtime[1];
				busterminus.m_beginTime = firsttime;
				busterminus.m_endTime = lasttime;
				//cout<<busterminus.m_lineID<<"=>"<<busterminus.m_lineName<<"=>"<<busterminus.m_terminusId<<"=>"<<busterminus.m_terminusName<<firsttime<<"=>"<<lasttime<<endl;

				busterminuss.push_back(busterminus);
			}
		}
	}
	return busterminuss;
}

vector<CBusPositionInfo> Cbusinfo::getBusPositonInfo(CBusTerminus lineStationInfo, string &src)
{
	Json::Reader reader;
	Json::Value value;
	vector<CBusPositionInfo> busPositions;
	busPositions.clear();

	if (reader.parse(src, value))
	{

			const Json::Value BusPosList = value["BusPosList"];
			int  BusPosNums = BusPosList.size();
			for(int BusPosNum = 0; BusPosNum < BusPosNums; ++BusPosNum)
			{
				CBusPositionInfo busPosition;
				busPosition.m_lineID = lineStationInfo.m_lineID;
				busPosition.m_lineName = lineStationInfo.m_lineName;
				//busPosition.m_stationID = lineStationInfo.m_stationID;
				//busPosition.m_stationName = lineStationInfo.m_stationName;
				busPosition.m_terminusId = lineStationInfo.m_terminusId;
				busPosition.m_terminusName = lineStationInfo.m_terminusName;
				//busPosition.m_stationPos.m_Latitude = lineStationInfo.m_stationPos.m_Latitude;
				//busPosition.m_stationPos.m_Longitude = lineStationInfo.m_stationPos.m_Longitude;

				busPosition.m_busId = BusPosList[BusPosNum]["BusID"].asString();
				busPosition.m_arriveTime = BusPosList[BusPosNum]["ArriveTime"].asString();
				busPosition.m_arriveStaInfo = BusPosList[BusPosNum]["ArriveStaInfo"].asString();
				busPosition.m_nextStaInfo = BusPosList[BusPosNum]["NextStaInfo"].asString();
				busPosition.m_Latitude = BusPosList[BusPosNum]["BusPostion"]["Latitude"].asDouble();
				busPosition.m_Longitude = BusPosList[BusPosNum]["BusPostion"]["Longitude"].asDouble();
/*
				cout<<busPosition.m_lineID<<"=>"<<busPosition.m_lineName;
				cout<<setprecision(8)<<"=>"<<busPosition.m_terminusId<<"=>"<<busPosition.m_terminusName;
				cout<<setprecision(8)<<"=>"<<busPosition.m_busId<<"=>"<<busPosition.m_arriveTime;
				cout<<setprecision(8)<<"=>"<<busPosition.m_arriveStaInfo<<"=>"<<busPosition.m_nextStaInfo<<"=>"<<busPosition.m_Latitude;
				cout<<setprecision(8)<<"=>"<<busPosition.m_Longitude<<endl;
*/
				string strlon, strlat;
				stringstream sslon, sslat;
				sslon<<busPosition.m_Longitude;
				sslon>>strlon;
				sslat<<busPosition.m_Latitude;
				sslat>>strlat;

				string linesrc;
				/*
				linesrc = busPosition.m_lineID+"=>"+busPosition.m_lineName
				+"=>"+busPosition.m_terminusId+"=>"+busPosition.m_terminusName
				+"=>"+busPosition.m_busId+"=>"+busPosition.m_arriveTime
				+"=>"+busPosition.m_arriveStaInfo+"=>"+busPosition.m_nextStaInfo+"=>"+strlat+"=>"+strlon;
				*/
				linesrc = busPosition.m_lineName+busPosition.m_terminusName+","+busPosition.m_busId+","+strlat+","+strlon+";";
				//LOG4CPLUS_DEBUG(ClogCPP::m_logger, linesrc.c_str());
				busPositions.push_back(busPosition);

			}
	}
	return busPositions;
}

CLineIdAndTerminusId Cbusinfo::getLineIdAndTerminusId(string &src)
{
	Json::Reader reader;
	Json::Value value;
	CLineIdAndTerminusId ids;

	if (reader.parse(src, value))
	{
		string lineID = value["lineID"].asString();
		string terminusId = value["terminusId"].asString();
		//cout<<"lineid: "<<lineID<<" , terminusId: "<<terminusId<<endl;
		ids.m_lineID = lineID;
		ids.m_terminusId = terminusId;
	}
	return ids;
}

string Cbusinfo::setJsonSrcs(vector<CBusPositionInfo> busPositionInfos)
{
    Json::Value root;
    Json::Value arrayObj;
    Json::Value item;
    for (int i=0; i<busPositionInfos.size(); i++)
    {
    	item["lineID"] = busPositionInfos[i].m_lineID;
    	item["lineName"] = busPositionInfos[i].m_lineName;
    	item["terminusId"] = busPositionInfos[i].m_terminusId;
    	item["terminusName"] = busPositionInfos[i].m_terminusName;
    	item["busId"] = busPositionInfos[i].m_busId;
    	item["arriveTime"] = busPositionInfos[i].m_arriveTime;
    	item["arriveStaInfo"] = busPositionInfos[i].m_arriveStaInfo;
    	item["nextStaInfo"] = busPositionInfos[i].m_nextStaInfo;
    	item["Latitude"] = busPositionInfos[i].m_Latitude;
    	item["Longitude"] = busPositionInfos[i].m_Longitude;
    	arrayObj.append(item);
    }

    root["BusPosList"] = arrayObj;
    root.toStyledString();
    std::string src = root.toStyledString();
    //std::cout << src << std::endl;
    return src;
}

string Cbusinfo::mergeJsonSrcs(vector< vector<CBusPositionInfo> > busPositionInfos)
{
    Json::Value root;
    Json::Value arrayline;
    for (int i=0; i<busPositionInfos.size(); i++)
    {
    	string src;
    	Json::Value item;
    	Json::Value arraybus;
    	for (int j=0; j<busPositionInfos[i].size(); j++)
    	{/*
        	item["lId"] = busPositionInfos[i][j].lineID;
        	item["lName"] = busPositionInfos[i][j].lineName;
        	item["tId"] = busPositionInfos[i][j].terminusId;
        	item["tName"] = busPositionInfos[i][j].terminusName;
        	item["busId"] = busPositionInfos[i][j].busId;
        	item["Time"] = busPositionInfos[i][j].arriveTime;
        	item["arrSta"] = busPositionInfos[i][j].arriveStaInfo;
        	item["nextSta"] = busPositionInfos[i][j].nextStaInfo;
        	item["Lat"] = busPositionInfos[i][j].Latitude;
        	item["Lon"] = busPositionInfos[i][j].Longitude;
        	*/
    		string strlon, strlat;
    		stringstream sslon, sslat;
    		sslon<<busPositionInfos[i][j].m_Longitude;
    		sslon>>strlon;
    		sslat<<busPositionInfos[i][j].m_Latitude;
    		sslat>>strlat;
        	src = busPositionInfos[i][j].m_lineID+"=>"+busPositionInfos[i][j].m_lineName+"=>"+busPositionInfos[i][j].m_terminusId+"=>"+
        			busPositionInfos[i][j].m_terminusName+"=>"+busPositionInfos[i][j].m_busId+"=>"+busPositionInfos[i][j].m_arriveTime+"=>"+
				busPositionInfos[i][j].m_arriveStaInfo+"=>"+busPositionInfos[i][j].m_nextStaInfo+"=>"
				+strlon+"=>"+strlat;
        	item[busPositionInfos[i][j].m_lineName] = src;
        	arraybus.append(item);
    	}

    	arrayline.append(arraybus);
    }
    root["BusPosList"] = arrayline;
    root.toStyledString();
    std::string src = root.toStyledString();
    //std::cout << src << std::endl;
    return src;
}

string Cbusinfo::mergeSrcs(vector< vector<CBusPositionInfo> > busPositionInfos)
{
	string dessrc;
	int num = 0;
    for (int i=0; i<busPositionInfos.size(); i++)
    {
    	for (int j=0; j<busPositionInfos[i].size(); j++)
    	{
    		string src;
    		string strlon, strlat;
    		stringstream sslon, sslat;
    		sslon<<setprecision(10)<<busPositionInfos[i][j].m_Longitude;
    		sslon>>strlon;
    		sslat<<setprecision(10)<<busPositionInfos[i][j].m_Latitude;
    		sslat>>strlat;
        	src = busPositionInfos[i][j].m_lineName+","+busPositionInfos[i][j].m_terminusName+","
        			+busPositionInfos[i][j].m_busId+","+strlon+","+strlat+";";

        	dessrc += src;
        	num++;
    	}
    }
    //LOG4CPLUS_DEBUG(ClogCPP::m_logger, dessrc);
    //LOG4CPLUS_INFO(ClogCPP::m_logger, num);
    return dessrc;
}

string Cbusinfo::mergeSrcslist(vector<CBusPositionInfo> busPositionInfos)
{
	string dessrc;
	int num = 0;
    for (int i=0; i<busPositionInfos.size(); i++)
    {
    	string src;
    	string strlon, strlat;
    	stringstream sslon, sslat;
    	sslon<<setprecision(10)<<busPositionInfos[i].m_Longitude;
    	sslon>>strlon;
    	sslat<<setprecision(10)<<busPositionInfos[i].m_Latitude;
    	sslat>>strlat;
        src = busPositionInfos[i].m_lineName+","+busPositionInfos[i].m_terminusName+","
        		+busPositionInfos[i].m_busId+","+strlon+","+strlat+";";

        dessrc += src;
        num++;
    }
    //LOG4CPLUS_DEBUG(ClogCPP::m_logger, dessrc);
    //LOG4CPLUS_INFO(ClogCPP::m_logger, num);
    return dessrc;
}

string Cbusinfo::setJsonSrc(CBusPositionInfo busPositionInfos)
{
    Json::Value item;

    item["lineID"] = busPositionInfos.m_lineID;
    item["lineName"] = busPositionInfos.m_lineName;
    item["terminusId"] = busPositionInfos.m_terminusId;
    item["terminusName"] = busPositionInfos.m_terminusName;
    item["busId"] = busPositionInfos.m_busId;
    item["arriveTime"] = busPositionInfos.m_arriveTime;
    item["arriveStaInfo"] = busPositionInfos.m_arriveStaInfo;
    item["nextStaInfo"] = busPositionInfos.m_nextStaInfo;
    item["Latitude"] = busPositionInfos.m_Latitude;
    item["Longitude"] = busPositionInfos.m_Longitude;

    std::string src = item.toStyledString();
    //std::cout << src << std::endl;
    return src;
}

vector<CthreadArgs> Cbusinfo::getArgsForThread()
{
    CURL *curl;
    const int LINE_LENGTH = 2048;
    char src[LINE_LENGTH+1];
    Ccrawl cr;
    vector<CthreadArgs> threadargss;
    CProxyIP ip;
    string str;
    vector<Cip_port> ips = ip.readProxy(PROXYCONF);
    int ips_length = ips.size();
    int ipnum = 0;

    FILE *fp = fopen(BUSLINECONF, "r");
    if(!fp)
    {
        printf("error file %s \n", BUSLINECONF);
        return threadargss;
    }
    while(1)
	{
      // 加锁以判断文件是否已经被加锁了
		if(flock(fileno(fp), LOCK_EX | LOCK_NB) == 0)
		{
			printf("file %s is unlock status \n", BUSLINECONF);
    		while ((fgets (src, LINE_LENGTH, fp)) != NULL)
			{
    			str = src;
    			int n = str.find_last_not_of(" \r\n\t");
    			//std::cout << "src: "<< str << std::endl;
    			if( n != string::npos )
    			{
    			    str.erase( n + 1 , str.size() - n );
    			}
    			std::vector<std::string> buslineinfo = cr.split(str, "---");
    	    	if(buslineinfo.size() >= 6)
    	    	{
    	        	CthreadArgs threadargs;
    	        	threadargs.m_curl = curl;
    	        	threadargs.m_ip = ips[ipnum].m_ip;
    	        	threadargs.m_port = ips[ipnum].m_port;
    	        	threadargs.m_busterminus.m_beginTime = buslineinfo[0];
    	    		threadargs.m_busterminus.m_endTime = buslineinfo[1];
    	        	threadargs.m_busterminus.m_lineID = buslineinfo[2];
    	        	threadargs.m_busterminus.m_lineName = buslineinfo[3];
    	        	threadargs.m_busterminus.m_terminusId = buslineinfo[4];
    	        	threadargs.m_busterminus.m_terminusName = buslineinfo[5];
    	        	threadargss.push_back(threadargs);
    	        	ipnum++;
    	        	if(ipnum >= ips_length)
    	        		ipnum = 0;
    	    	}
			}
			fclose(fp);
			flock(fileno(fp), LOCK_UN);
			break;
		}
		else
		{
			printf("file %s is locked, please wait \n", BUSLINECONF);
			sleep(1);
		}
	}

    return threadargss;
}

void* Cbusinfo::runUrl(void *arg)
{
	//LOG4CPLUS_DEBUG(ClogCPP::m_logger, "runUrl begin....");
	CthreadArgs *threadargs = (CthreadArgs *)arg;

	string url = "http://222.85.139.244:1001/BusService/QueryDetail_ByRouteID/?RouteID="
			+threadargs->m_busterminus.m_lineID+"&SegmentID="+threadargs->m_busterminus.m_terminusId;
	//cout<<"<*****url*****>"<<url<<" "<<threadargs->m_ip<<":"<<threadargs->m_port<<endl;
	string buslines_src;
	CgetDataFromUrl getdata;
	Cbusinfo bus;

	int flag = bus.IsInTimeSpan(threadargs->m_busterminus.m_beginTime, threadargs->m_busterminus.m_endTime);
	if(flag == -1)
	{
		//cout<<threadargs->m_busterminus.m_lineName<<" 公交车处于休息时间"<<endl;
	    return NULL;
	}
	buslines_src = getdata.getBusInfoByUrl(threadargs->m_curl, url, threadargs->m_ip, threadargs->m_port, true); //set proxy
	if(buslines_src.length() <= 0)
	{
		//printf("set proxy ip: %s, port: %d false=====>\n", threadargs->m_ip.c_str(), threadargs->m_port);
	    buslines_src = getdata.getBusInfoByUrl(threadargs->m_curl, url, threadargs->m_ip, threadargs->m_port, false); //not set proxy
	}
	//cout<<"<*****buslines_src*****>"<<buslines_src<<endl;
	vector<CBusPositionInfo> busPositionInfos = bus.getBusPositonInfo(threadargs->m_busterminus, buslines_src);
	//LOG4CPLUS_DEBUG(ClogCPP::m_logger, "busPositionInfos size()=====>"+busPositionInfos.size());

	if(pthread_mutex_lock(&BACK_COMM_mutex)!=0)
	{
		printf("buslist pthread_mutex_lock err !!\n");
        return NULL;
	}
	if(busPositionInfos.size() != 0)
		threadargs->m_buslist->push_back(busPositionInfos);
	if(pthread_mutex_unlock(&BACK_COMM_mutex)!=0) //unlock
    {
		printf("buslist pthread_mutex_unlock err !!\n");
		return NULL;
    }
	//LOG4CPLUS_DEBUG(ClogCPP::m_logger, "runUrl end....");
	return NULL;
}

void Cbusinfo::runPthread(CpoolBuslist *buslistinfo)
{
	//LOG4CPLUS_DEBUG(ClogCPP::m_logger, "runPthread begin....");
    int urllines = buslistinfo->m_cbuslist->m_threadargss.size();
    Cthreadpool *thread_pool = buslistinfo->m_thread_pool;
    //cout<<"urllines===>"<<urllines<<endl;
    buslistinfo->m_cbuslist->m_buslist.clear();
    time_t tt = time(NULL);
    tm* t1= localtime(&tt);
    char time1[100];
    sprintf(time1, "%d-%02d-%02d %02d:%02d:%02d\n", t1->tm_year + 1900,t1->tm_mon + 1,t1->tm_mday,t1->tm_hour,t1->tm_min,t1->tm_sec);

    for (int i = 0; i < urllines; i++)
    {
    	buslistinfo->m_cbuslist->m_threadargss[i].m_buslist = &buslistinfo->m_cbuslist->m_buslist;
    	thread_pool->pool_add_worker (Cbusinfo::runUrl, &buslistinfo->m_cbuslist->m_threadargss[i]);
    }
    sleep(1);
    while(1)
    {
    	if(thread_pool->pool->cur_queue_size == 0)
    	{
    		cout<<"====pool is empty=======\n";
    		break;
    	}
    	sleep(1);
    	continue;
    }
    time_t tt1 = time(NULL);
    tm* t2= localtime(&tt1);
    char time2[100];
    sprintf(time2, "%d-%02d-%02d %02d:%02d:%02d\n", t2->tm_year + 1900,t2->tm_mon + 1,t2->tm_mday,t2->tm_hour,t2->tm_min,t2->tm_sec);
    cout<<"begin time: "<<time1;
    cout<<"end   time: "<<time2;
    //LOG4CPLUS_DEBUG(ClogCPP::m_logger, "runPthread end....");
}

int Cbusinfo::IsInTimeSpan(string &begintime, string &endtime)
{
	Ccrawl cr;
	vector<string> local_time = cr.split(begintime, ":");
	if(local_time.size() < 2)
	{
		LOG4CPLUS_ERROR(ClogCPP::m_logger, "IsInTimeSpan error....");
		return -1;
	}

	int begin_h = (atoi(local_time[0].c_str()) + 24 - 1) % 24; //-1
	int begin_m = atoi(local_time[1].c_str());
	local_time.clear();
	local_time = cr.split(endtime, ":");
	int end_h = (atoi(local_time[0].c_str()) + 2) % 24; //+2
	int end_m = atoi(local_time[1].c_str());
	time_t tt = time(NULL);
	tm* t= localtime(&tt);
    int now_h = t->tm_hour;
    int now_m = t->tm_min;

    int iBegLessThanEnd = 0;       // 1-配置的开始时间小于结束时间  0-配置的开始时间大于结束时间
    int flag = 0;

    if (begin_h < end_h || (begin_h == end_h && begin_m <= end_m))
    {
        iBegLessThanEnd = 1;
    }
    else
    {
        iBegLessThanEnd = 0;
    }

    if (iBegLessThanEnd)   // 开始时间小于结束时间
    {
         if ((now_h > begin_h || (now_h == begin_h && now_m >= begin_m))
            && (now_h < end_h || (now_h == end_h && now_m <= end_m)))
         {
        	 flag = 0;
         }
         else
         {
        	 flag = -1;
         }
    }
    else   // 开始时间大于结束时间, 跨天的情况
    {
         if ((now_h > begin_h || (now_h == begin_h && now_m >= begin_m))
            || (now_h < end_h || (now_h == end_h && now_m <= end_m)))
         {
        	 flag = 0;
         }
         else
         {
        	 flag = -1;
         }
    }
    //cout<<begin_h<<":"<<begin_m<<","<<end_h<<":"<<end_m<<","<<now_h<<":"<<now_m<<"==>"<<flag<<endl;
    return flag;
}

void Cbusinfo::copyBusList(vector<CBusPositionInfo> &desc, const vector< vector<CBusPositionInfo> > &src)
{
	int desc_nums = src.size();
	int desc_num;
	for(int src_nums = 0; src_nums < desc_nums; ++src_nums)
	{
		desc_num = src[src_nums].size();
		for(int src_num = 0; src_num < desc_num; ++src_num)
		{
			desc.push_back(src[src_nums][src_num]);
		}
	}
}

vector<CBusPositionInfo> Cbusinfo::checkNewBusList(const vector<CBusPositionInfo> &desc, const vector< vector<CBusPositionInfo> > &src)
{
	vector<CBusPositionInfo> newbuslist;

	int desc_nums = src.size();
	int desc_num;
	for(int src_nums = 0; src_nums < desc_nums; ++src_nums)
	{
		desc_num = src[src_nums].size();
		for(int src_num = 0; src_num < desc_num; ++src_num)
		{
			if(checkBusLineExist(src[src_nums][src_num], desc) == false)
			{
				newbuslist.push_back(src[src_nums][src_num]);
			}
		}
	}
	return newbuslist;
}

bool Cbusinfo::checkBusLineExist(CBusPositionInfo desc, const vector<CBusPositionInfo>  &src)
{
	int desc_num = src.size();
	bool flag = false;
	for(int src_num = 0; src_num < desc_num; ++src_num)
	{
		if(((src[src_num].m_Latitude - desc.m_Latitude >= -0.00001 && src[src_num].m_Latitude - desc.m_Latitude <= 0.00001)
			|| (src[src_num].m_Longitude - desc.m_Longitude >= -0.00001 && src[src_num].m_Longitude - desc.m_Longitude <= 0.00001))
			&& (src[src_num].m_busId == desc.m_busId))
		{
			flag = true;
			break;
		}
	}
	return flag;
}



