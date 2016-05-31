/*
 * businfo.cpp
 *
 *  Created on: May 17, 2016
 *      Author: mxj
 */

#include "businfo.h"
#include<iomanip>
#include <sstream>
#include <pthread.h>
#include "crawl.h"
#include "getProxy.h"
#include "getDataFromUrl.h"
#include "threadpool.h"
#include "common.h"


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

vector<CBusTerminus> Cbusinfo::getBusTerminus(FILE *pbusline, string &src)
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

				//cout<<busterminus.m_lineID<<"=>"<<busterminus.m_lineName<<"=>"<<busterminus.m_terminusId<<"=>"<<busterminus.m_terminusName<<endl;
				fprintf(pbusline, "%s---%s---%s---%s\n",busterminus.m_lineID.c_str(), busterminus.m_lineName.c_str(), busterminus.m_terminusId.c_str(), busterminus.m_terminusName.c_str());
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
				linesrc = busPosition.m_lineID+"=>"+busPosition.m_lineName
				+"=>"+busPosition.m_terminusId+"=>"+busPosition.m_terminusName
				+"=>"+busPosition.m_busId+"=>"+busPosition.m_arriveTime
				+"=>"+busPosition.m_arriveStaInfo+"=>"+busPosition.m_nextStaInfo+"=>"+strlat+"=>"+strlon;
				//cout<<"line:====>"<<linesrc<<endl;
				LOG4CPLUS_DEBUG(ClogCPP::m_logger, linesrc.c_str());
				//LOG4CPLUS_INFO(logCPP::logger, "info");
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

string Cbusinfo::mergeJsonSrcs(vector<vector<CBusPositionInfo> > busPositionInfos)
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
				+strlat+"=>"+strlon;
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
    char str[LINE_LENGTH];
    Ccrawl cr;
    vector<CthreadArgs> threadargss;
    ifstream fin("conf/busline.conf");
    CProxyIP ip;
    vector<Cip_port> ips = ip.readProxy("conf/proxy.conf");
    int ips_length = ips.size();
    int ipnum = 0;
    while( fin.getline(str,LINE_LENGTH) != NULL)
    {
        //std::cout << "Read from file: " << str << std::endl;
    	std::vector<std::string> buslineinfo = cr.split(str, "---");
    	CthreadArgs threadargs;
    	threadargs.m_curl = curl;
    	threadargs.m_ip = ips[ipnum].m_ip;
    	threadargs.m_port = ips[ipnum].m_port;
    	threadargs.m_busterminus.m_lineID = buslineinfo[0];
    	threadargs.m_busterminus.m_lineName = buslineinfo[1];
    	threadargs.m_busterminus.m_terminusId = buslineinfo[2];
    	threadargs.m_busterminus.m_terminusName = buslineinfo[3];
    	threadargss.push_back(threadargs);
    	ipnum++;
    	if(ipnum >= ips_length)
    		ipnum = 0;
    }

    return threadargss;
}

void* Cbusinfo::runUrl(void *arg)
{
	CthreadArgs *threadargs = (CthreadArgs *)arg;

	string url = "http://222.85.139.244:1001/BusService/QueryDetail_ByRouteID/?RouteID="
			+threadargs->m_busterminus.m_lineID+"&SegmentID="+threadargs->m_busterminus.m_terminusId;
	cout<<"<*****url*****>"<<url<<" "<<threadargs->m_ip<<":"<<threadargs->m_port<<endl;
	string buslines_src;
	CgetDataFromUrl getdata;
	buslines_src = getdata.getBusInfoByUrl(threadargs->m_curl, url, threadargs->m_ip, threadargs->m_port, true); //set proxy
	if(buslines_src.length() <= 0)
	{
		cout<<"set proxy false=====>\n";
	    buslines_src = getdata.getBusInfoByUrl(threadargs->m_curl, url, threadargs->m_ip, threadargs->m_port, false); //not set proxy
	}
	//cout<<"<*****buslines_src*****>"<<buslines_src<<endl;
	Cbusinfo bus;
	vector<CBusPositionInfo> busPositionInfos = bus.getBusPositonInfo(threadargs->m_busterminus, buslines_src);
	//cout<<"busPositionInfos size()=====>"<<busPositionInfos.size()<<endl;
	LOG4CPLUS_DEBUG(ClogCPP::m_logger, "busPositionInfos size()=====>"+busPositionInfos.size());

	if(pthread_mutex_lock(&BACK_COMM_mutex)!=0)
	{
        printf("buslist BACK_COMM_mutex lock err !!\n");
        return NULL;
	}
	if(busPositionInfos.size() != 0)
		threadargs->m_buslist->push_back(busPositionInfos);
	if(pthread_mutex_unlock(&BACK_COMM_mutex)!=0) //unlock
    {
		printf("buslist pthread_mutex_unlock err !!\n");
		return NULL;
    }
	return NULL;
}

void Cbusinfo::runPthread(CpoolBuslist *buslistinfo)
{
    int urllines = buslistinfo->m_cbuslist->m_threadargss.size();
    Cthreadpool *thread_pool = buslistinfo->m_thread_pool;
    cout<<"urllines===>"<<urllines<<endl;
    buslistinfo->m_cbuslist->m_buslist.clear();
    time_t tt = time(NULL);
    tm* t1= localtime(&tt);
    char time1[100];
    sprintf(time1, "%d-%02d-%02d %02d:%02d:%02d\n", t1->tm_year + 1900,t1->tm_mon + 1,t1->tm_mday,t1->tm_hour,t1->tm_min,t1->tm_sec);

    for (int i = 0; i < urllines; i++) {
    	buslistinfo->m_cbuslist->m_threadargss[i].m_buslist = &buslistinfo->m_cbuslist->m_buslist;
    	thread_pool->pool_add_worker (Cbusinfo::runUrl, &buslistinfo->m_cbuslist->m_threadargss[i]);
    }
    sleep(2);
    while(1)
    {
    	if(thread_pool->pool->cur_queue_size == 0)
    	{
    		break;
    		cout<<"===========exit\n";
    	}
    	sleep(2);
    	continue;
    }
    time_t tt1 = time(NULL);
    tm* t2= localtime(&tt1);
    char time2[100];
    sprintf(time2, "%d-%02d-%02d %02d:%02d:%02d\n", t2->tm_year + 1900,t2->tm_mon + 1,t2->tm_mday,t2->tm_hour,t2->tm_min,t2->tm_sec);
    cout<<"begin time: "<<time1;
    cout<<"end   time: "<<time2;
}


