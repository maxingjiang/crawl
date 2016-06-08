/*
 * businfo.h
 *
 *  Created on: May 17, 2016
 *      Author: mxj
 */

#ifndef INCLUDE_BUSINFO_H_
#define INCLUDE_BUSINFO_H_

#include <iostream>
#include <string>
#include "json/json.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "threadpool.h"

using namespace :: std;
using namespace :: Json;
using std::string;

class CPos
{
public:
	double m_Latitude;
	double m_Longitude;
};

class CBusAllLine
{
public:
    string m_lineID;
    string m_lineName;
};

class CLineIdAndTerminusId
{
public:
    string m_lineID;
    string m_terminusId;
};

class CBusStation
{
public:
    string m_lineID;
    string m_lineName;
    string m_terminusId;
    string m_terminusName;
    string m_stationID;
    string m_stationName;
    CPos m_stationPos;
};

class CBusTerminus
{
public:
    string m_lineID;
    string m_lineName;
    string m_terminusId;
    string m_terminusName;
    string m_beginTime;
    string m_endTime;
};

class CBusPositionInfo
{
public:
	string m_lineID;
	string m_lineName;
	string m_terminusId;
	string m_terminusName;
	string m_busId;
	string m_stationID;
	string m_stationName;
	CPos m_stationPos;
	string m_arriveTime;
	string m_arriveStaInfo;
	string m_nextStaInfo;
	double m_Latitude;
	double m_Longitude;
};

class CthreadArgs
{
public:
	CURL *m_curl;
	CBusTerminus m_busterminus;
	string m_ip;
	int m_port;
	vector< vector<CBusPositionInfo> > *m_buslist;
};

class CBusLists
{
public:
	vector< vector<CBusPositionInfo> > m_buslist;
	vector<CthreadArgs> m_threadargss;
};

class CpoolBuslist
{
public:
	Cthreadpool *m_thread_pool;
	CBusLists *m_cbuslist;
};
/* buslist descreption
 * 0:lineID
 * 1:lineName
 * 2:terminusId
 * 3:terminusName
 * 4:busId
 * 5:arriveTime
 * 6:arriveStaInfo
 * 7:nextStaInfo
 * 8:Latitude
 * 9:Longitude
 * */

class Cbusinfo
{
	public:
		void clearInfo();

		void setInfo(string lineID, string lineName, string terminusId, string terminusName,
				string busId, string stationID, string stationName, string arriveTime,
				string arriveStaInfo, string nextStaInfo, double Latitude, double Longitude);

		vector<CBusAllLine> getAllLineInfo(string &src); //get all lines

		vector<CBusStation> getBusStation(string &src); //get all stations of every line

		vector<CBusTerminus> getBusTerminus(string &src); //get terminus station of every line

		vector<CBusPositionInfo> getBusPositonInfo(CBusTerminus lineStationInfo, string &src); //get pos info of bus

		CLineIdAndTerminusId getLineIdAndTerminusId(string &src); //get line id and terminus id

		string setJsonSrcs(vector<CBusPositionInfo> busPositionInfos); //set struct to json string
		string setJsonSrc(CBusPositionInfo busPositionInfos); //set struct to json string
		string mergeJsonSrcs(vector< vector<CBusPositionInfo> > busPositionInfos); //merge all json info
		string mergeSrcs(vector< vector<CBusPositionInfo> > busPositionInfos); //merge all info
		string mergeSrcslist(vector<CBusPositionInfo> busPositionInfos);

		void runPthread(CpoolBuslist *buslistinfo);  //get all data

		//use by threadpool
		vector<CthreadArgs> getArgsForThread();
		static void* runUrl(void *arg);

		int IsInTimeSpan(string &begintime, string &endtime); //now is in time region or not(format:06:30:00)

		void copyBusList(vector<CBusPositionInfo> &desc, const vector< vector<CBusPositionInfo> > &src);

		vector<CBusPositionInfo> checkNewBusList(const vector<CBusPositionInfo> &desc, const vector< vector<CBusPositionInfo> > &src);

		bool checkBusLineExist(CBusPositionInfo desc, const vector<CBusPositionInfo>  &src);


	public:
		CBusPositionInfo m_bus;
		/*
		string m_lineID;
		string m_lineName;
		string m_terminusId;
		string m_terminusName;
		string m_busId;
		string m_stationID;
		string m_stationName;
		pos m_stationPos;
		string m_arriveTime;
		string m_arriveStaInfo;
		string m_nextStaInfo;
		pos m_busPos;
		*/
};

#endif /* INCLUDE_BUSINFO_H_ */
