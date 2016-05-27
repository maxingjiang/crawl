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

using namespace :: std;
using namespace :: Json;
using std::string;

struct pos
{
	double Latitude;
	double Longitude;
};

struct busAllLine
{
    string lineID;
    string lineName;
};

struct LineIdAndTerminusId
{
    string lineID;
    string terminusId;
};

struct busStation
{
    string lineID;
    string lineName;
    string terminusId;
    string terminusName;
    string stationID;
    string stationName;
    pos stationPos;
};

struct busTerminus
{
    string lineID;
    string lineName;
    string terminusId;
    string terminusName;
};

struct busPositionInfo
{
	string lineID;
	string lineName;
	string terminusId;
	string terminusName;
	string busId;
	string stationID;
	string stationName;
	pos stationPos;
	string arriveTime;
	string arriveStaInfo;
	string nextStaInfo;
	double Latitude;
	double Longitude;
};

struct threadArgs
{
	CURL *curl;
	busTerminus busterminus;
	string ip;
	int port;
};

class busLists
{
public:
	static vector< vector<busPositionInfo> > buslist;
	static vector<threadArgs> threadargss;
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

class businfo
{
	public:
		void clearInfo();

		void setInfo(string lineID, string lineName, string terminusId, string terminusName,
				string busId, string stationID, string stationName, string arriveTime,
				string arriveStaInfo, string nextStaInfo, double Latitude, double Longitude);

		vector<busAllLine> getAllLineInfo(string &src); //get all lines

		vector<busStation> getBusStation(string &src); //get all stations of every line

		vector<busTerminus> getBusTerminus(FILE *pbusline, string &src); //get terminus station of every line

		vector<busPositionInfo> getBusPositonInfo(busTerminus lineStationInfo, string &src); //get pos info of bus

		LineIdAndTerminusId getLineIdAndTerminusId(string &src); //get line id and terminus id

		string setJsonSrcs(vector<busPositionInfo> busPositionInfos); //set struct to json string
		string setJsonSrc(busPositionInfo busPositionInfos); //set struct to json string
		string mergeJsonSrcs(vector<vector<busPositionInfo> > busPositionInfos); //merge all json info
		void runPthread();  //get all data

		//use by threadpool
		vector<threadArgs> getArgsForThread();
		static void* runUrl(void *arg);


	public:
		busPositionInfo bus;
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
