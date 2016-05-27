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

pthread_mutex_t BACK_COMM_mutex = PTHREAD_MUTEX_INITIALIZER ;
vector< vector<busPositionInfo> > busLists::buslist;
vector<threadArgs> busLists::threadargss;

void businfo::clearInfo()
{
	bus.lineID = "";
	bus.lineName = "";
	bus.terminusId = "";
	bus.terminusName = "";
	bus.busId = "";
	bus.stationID = "";
	bus.stationName = "";
	bus.arriveTime = "";
	bus.arriveStaInfo = "";
	bus.nextStaInfo = "";
	bus.Latitude = 0.0;
	bus.Longitude = 0.0;
}

void businfo::setInfo(string lineID, string lineName, string terminusId, string terminusName,
				string busId, string stationID, string stationName, string arriveTime,
				string arriveStaInfo, string nextStaInfo, double Latitude, double Longitude)
{
	bus.lineID = lineID;
	bus.lineName = lineName;
	bus.terminusId = terminusId;
	bus.terminusName = terminusName;
	bus.busId = busId;
	bus.stationID = stationID;
	bus.stationName = stationName;
	bus.arriveTime = arriveTime;
	bus.arriveStaInfo = arriveStaInfo;
	bus.nextStaInfo = nextStaInfo;
	bus.Latitude = Latitude;
	bus.Longitude = Longitude;
}

vector<busAllLine> businfo::getAllLineInfo(string &src)
{
	Json::Reader reader;
	Json::Value value;
	vector<busAllLine> allline;
	allline.clear();

	if (reader.parse(src, value))
	{
		const Json::Value arrayNum = value["RouteList"];

		int file_size = arrayNum.size();
		for(int i = 0; i < file_size; ++i)
		{
			busAllLine line;
			string lineID = arrayNum[i]["RouteID"].asString();
			string lineName = arrayNum[i]["RouteName"].asString();
			line.lineID = lineID;
			line.lineName = lineName;
			//cout<<lineID<<": "<<lineName<<endl;
			allline.push_back(line);
		}
	}
	return allline;
}

vector<busStation> businfo::getBusStation(string &src)
{
	Json::Reader reader;
	Json::Value value;
	vector<busStation> busstation;
	busstation.clear();

	if (reader.parse(src, value))
	{
		int arrayNum = value.size();

		for(int i = 0; i < arrayNum; ++i)
		{
			busStation lineStationInfo;

			lineStationInfo.lineID = value[i]["RouteID"].asString();
			lineStationInfo.lineName = value[i]["RouteName"].asString();

			const Json::Value terminusList = value[i]["SegmentList"];
			int  terminusNum = terminusList.size();
			for(int terminus = 0; terminus < terminusNum; ++terminus)
			{
				lineStationInfo.terminusId = terminusList[terminus]["SegmentID"].asString();
				lineStationInfo.terminusName = terminusList[terminus]["SegmentName"].asString();

				const Json::Value stationList = terminusList[terminus]["StationList"];
				int  stationNum = stationList.size();
				for(int station = 0; station < stationNum; ++station)
				{
					lineStationInfo.stationID = stationList[station]["StationID"].asString();
					lineStationInfo.stationName = stationList[station]["StationName"].asString();
					lineStationInfo.stationPos.Latitude = stationList[station]["StationPostion"]["Latitude"].asDouble();
					lineStationInfo.stationPos.Longitude = stationList[station]["StationPostion"]["Longitude"].asDouble();
					/*cout<<lineStationInfo.lineID<<"=>"<<lineStationInfo.lineName<<"=>"<<lineStationInfo.terminusId
							<<"=>"<<lineStationInfo.terminusName<<"=>"<<lineStationInfo.stationID<<"=>"<<lineStationInfo.stationName
							<<"=>"<<lineStationInfo.stationPos.Latitude<<"=>"<<lineStationInfo.stationPos.Longitude<<endl;*/
					busstation.push_back(lineStationInfo);
				}
			}
		}
	}
	return busstation;
}

vector<busTerminus> businfo::getBusTerminus(FILE *pbusline, string &src)
{
	Json::Reader reader;
	Json::Value value;
	vector<busTerminus> busterminuss;
	busterminuss.clear();

	if (reader.parse(src, value))
	{
		int arrayNum = value.size();

		for(int i = 0; i < arrayNum; ++i)
		{
			busTerminus busterminus;

			busterminus.lineID = value[i]["RouteID"].asString();
			busterminus.lineName = value[i]["RouteName"].asString();

			const Json::Value terminusList = value[i]["SegmentList"];
			int  terminusNum = terminusList.size();
			for(int terminus = 0; terminus < terminusNum; ++terminus)
			{
				busterminus.terminusId = terminusList[terminus]["SegmentID"].asString();
				busterminus.terminusName = terminusList[terminus]["SegmentName"].asString();

				//cout<<busterminus.lineID<<"=>"<<busterminus.lineName<<"=>"<<busterminus.terminusId<<"=>"<<busterminus.terminusName<<endl;
				fprintf(pbusline, "%s---%s---%s---%s\n",busterminus.lineID.c_str(), busterminus.lineName.c_str(), busterminus.terminusId.c_str(), busterminus.terminusName.c_str());
				busterminuss.push_back(busterminus);
			}
		}
	}
	return busterminuss;
}

vector<busPositionInfo> businfo::getBusPositonInfo(busTerminus lineStationInfo, string &src)
{
	Json::Reader reader;
	Json::Value value;
	vector<busPositionInfo> busPositions;
	busPositions.clear();

	if (reader.parse(src, value))
	{

			const Json::Value BusPosList = value["BusPosList"];
			int  BusPosNums = BusPosList.size();
			for(int BusPosNum = 0; BusPosNum < BusPosNums; ++BusPosNum)
			{
				busPositionInfo busPosition;
				busPosition.lineID = lineStationInfo.lineID;
				busPosition.lineName = lineStationInfo.lineName;
				//busPosition.stationID = lineStationInfo.stationID;
				//busPosition.stationName = lineStationInfo.stationName;
				busPosition.terminusId = lineStationInfo.terminusId;
				busPosition.terminusName = lineStationInfo.terminusName;
				//busPosition.stationPos.Latitude = lineStationInfo.stationPos.Latitude;
				//busPosition.stationPos.Longitude = lineStationInfo.stationPos.Longitude;

				busPosition.busId = BusPosList[BusPosNum]["BusID"].asString();
				busPosition.arriveTime = BusPosList[BusPosNum]["ArriveTime"].asString();
				busPosition.arriveStaInfo = BusPosList[BusPosNum]["ArriveStaInfo"].asString();
				busPosition.nextStaInfo = BusPosList[BusPosNum]["NextStaInfo"].asString();
				busPosition.Latitude = BusPosList[BusPosNum]["BusPostion"]["Latitude"].asDouble();
				busPosition.Longitude = BusPosList[BusPosNum]["BusPostion"]["Longitude"].asDouble();

				cout<<busPosition.lineID<<"=>"<<busPosition.lineName;
				cout<<setprecision(8)<<"=>"<<busPosition.terminusId<<"=>"<<busPosition.terminusName;
				cout<<setprecision(8)<<"=>"<<busPosition.busId<<"=>"<<busPosition.arriveTime;
				cout<<setprecision(8)<<"=>"<<busPosition.arriveStaInfo<<"=>"<<busPosition.nextStaInfo<<"=>"<<busPosition.Latitude;
				cout<<setprecision(8)<<"=>"<<busPosition.Longitude<<endl;
				busPositions.push_back(busPosition);

			}
	}
	return busPositions;
}

LineIdAndTerminusId businfo::getLineIdAndTerminusId(string &src)
{
	Json::Reader reader;
	Json::Value value;
	LineIdAndTerminusId ids;

	if (reader.parse(src, value))
	{
		string lineID = value["lineID"].asString();
		string terminusId = value["terminusId"].asString();
		//cout<<"lineid: "<<lineID<<" , terminusId: "<<terminusId<<endl;
		ids.lineID = lineID;
		ids.terminusId = terminusId;
	}
	return ids;
}

string businfo::setJsonSrcs(vector<busPositionInfo> busPositionInfos)
{
    Json::Value root;
    Json::Value arrayObj;
    Json::Value item;
    for (int i=0; i<busPositionInfos.size(); i++)
    {
    	item["lineID"] = busPositionInfos[i].lineID;
    	item["lineName"] = busPositionInfos[i].lineName;
    	item["terminusId"] = busPositionInfos[i].terminusId;
    	item["terminusName"] = busPositionInfos[i].terminusName;
    	item["busId"] = busPositionInfos[i].busId;
    	item["arriveTime"] = busPositionInfos[i].arriveTime;
    	item["arriveStaInfo"] = busPositionInfos[i].arriveStaInfo;
    	item["nextStaInfo"] = busPositionInfos[i].nextStaInfo;
    	item["Latitude"] = busPositionInfos[i].Latitude;
    	item["Longitude"] = busPositionInfos[i].Longitude;
    	arrayObj.append(item);
    }

    root["BusPosList"] = arrayObj;
    root.toStyledString();
    std::string src = root.toStyledString();
    //std::cout << src << std::endl;
    return src;
}

string businfo::mergeJsonSrcs(vector<vector<busPositionInfo> > busPositionInfos)
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
    		sslon<<busPositionInfos[i][j].Longitude;
    		sslon>>strlon;
    		sslat<<busPositionInfos[i][j].Latitude;
    		sslat>>strlat;
        	src = busPositionInfos[i][j].lineID+"=>"+busPositionInfos[i][j].lineName+"=>"+busPositionInfos[i][j].terminusId+"=>"+
        			busPositionInfos[i][j].terminusName+"=>"+busPositionInfos[i][j].busId+"=>"+busPositionInfos[i][j].arriveTime+"=>"+
				busPositionInfos[i][j].arriveStaInfo+"=>"+busPositionInfos[i][j].nextStaInfo+"=>"
				+strlat+"=>"+strlon;
        	item["lName"] = src;
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

string businfo::setJsonSrc(busPositionInfo busPositionInfos)
{
    Json::Value item;

    item["lineID"] = busPositionInfos.lineID;
    item["lineName"] = busPositionInfos.lineName;
    item["terminusId"] = busPositionInfos.terminusId;
    item["terminusName"] = busPositionInfos.terminusName;
    item["busId"] = busPositionInfos.busId;
    item["arriveTime"] = busPositionInfos.arriveTime;
    item["arriveStaInfo"] = busPositionInfos.arriveStaInfo;
    item["nextStaInfo"] = busPositionInfos.nextStaInfo;
    item["Latitude"] = busPositionInfos.Latitude;
    item["Longitude"] = busPositionInfos.Longitude;

    std::string src = item.toStyledString();
    //std::cout << src << std::endl;
    return src;
}

vector<threadArgs> businfo::getArgsForThread()
{
    CURL *curl;
    const int LINE_LENGTH = 2048;
    char str[LINE_LENGTH];
    crawl cr;
    cr.clear();
    vector<threadArgs> threadargss;
    ifstream fin("conf/busline.conf");
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
    }

    return threadargss;
}

void* businfo::runUrl(void *arg)
{
	threadArgs *threadargs = (threadArgs *)arg;
	string url = "http://222.85.139.244:1001/BusService/QueryDetail_ByRouteID/?RouteID="
			+threadargs->busterminus.lineID+"&SegmentID="+threadargs->busterminus.terminusId;
	cout<<"<*****url*****>"<<url<<" "<<threadargs->ip<<":"<<threadargs->port<<endl;
	string buslines_src;
	getDataFromUrl getdata;
	buslines_src = getdata.getBusInfoByUrl(threadargs->curl, url, threadargs->ip, threadargs->port, true); //set proxy
	if(buslines_src.length() <= 0)
	{
		cout<<"false=====\n";
	    buslines_src = getdata.getBusInfoByUrl(threadargs->curl, url, threadargs->ip, threadargs->port, false); //not set proxy
	}
	//cout<<"<*****buslines_src*****>"<<buslines_src<<endl;
	businfo bus;
	vector<busPositionInfo> busPositionInfos = bus.getBusPositonInfo(threadargs->busterminus, buslines_src);
	cout<<"busPositionInfos size()=====>"<<busPositionInfos.size()<<endl;


	if(pthread_mutex_lock(&BACK_COMM_mutex)!=0)
	{
        printf("buslist BACK_COMM_mutex lock err !!\n");
        return NULL;
	}
	if(busPositionInfos.size() != 0)
		busLists::buslist.push_back(busPositionInfos);
	if(pthread_mutex_unlock(&BACK_COMM_mutex)!=0) //unlock
    {
		printf("buslist pthread_mutex_unlock err !!\n");
		return NULL;
    }
}

void businfo::runPthread()
{
    int urllines = busLists::threadargss.size();
    cout<<"urllines===>"<<urllines<<endl;
    busLists::buslist.clear();
    time_t tt = time(NULL);
    tm* t1= localtime(&tt);
    char time1[100];
    sprintf(time1, "%d-%02d-%02d %02d:%02d:%02d\n", t1->tm_year + 1900,t1->tm_mon + 1,t1->tm_mday,t1->tm_hour,t1->tm_min,t1->tm_sec);

    for (int i = 0; i < 4; i++) {
    	threadpool::pool_add_worker (businfo::runUrl, &busLists::threadargss[i]);
    }
    sleep(2);
    while(1)
    {
    	if(threadpool::pool->cur_queue_size == 0)
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
    cout<<"begin time"<<time1;
    cout<<"end time"<<time2;
}


