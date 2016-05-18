/*
 * businfo.cpp
 *
 *  Created on: May 17, 2016
 *      Author: mxj
 */
#include "businfo.h"
#include<iomanip>

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
	bus.busPos.Latitude = 0.0;
	bus.busPos.Longitude = 0.0;
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
	bus.busPos.Latitude = Latitude;
	bus.busPos.Longitude = Longitude;
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
					lineStationInfo.stationPos.Latitude = stationList[station]["StationPostion"]["Latitude"].asFloat();
					lineStationInfo.stationPos.Longitude = stationList[station]["StationPostion"]["Longitude"].asFloat();
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
				busPosition.busPos.Latitude = BusPosList[BusPosNum]["BusPostion"]["Latitude"].asFloat();
				busPosition.busPos.Longitude = BusPosList[BusPosNum]["BusPostion"]["Longitude"].asFloat();

				cout<<busPosition.lineID<<"=>"<<busPosition.lineName;
				cout<<setprecision(8)<<"=>"<<busPosition.terminusId<<"=>"<<busPosition.terminusName;
				cout<<setprecision(8)<<"=>"<<busPosition.busId<<"=>"<<busPosition.arriveTime;
				cout<<setprecision(8)<<"=>"<<busPosition.arriveStaInfo<<"=>"<<busPosition.nextStaInfo<<"=>"<<busPosition.busPos.Latitude;
				cout<<setprecision(8)<<"=>"<<busPosition.busPos.Longitude<<endl;
				busPositions.push_back(busPosition);

			}
	}
	return busPositions;
}




