#include "CDBServer.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

void testmysql()
{
	string host = "127.0.0.1";
	string user = "root";
	string pass = "123456";
	string dbname = "crawldb";
	int poolSize = 10;
	CDBServer dbcrawl;
	dbcrawl.initMysqlPool(host,user,pass,dbname,poolSize);
	Connection* connect = dbcrawl.getConnection();

	if(!connect){
		cout << "getConnection NULL pointer" << endl;
		exit(-1);
	}
	int i = 10000;
	while(i--)
	{
		string strlon;
		stringstream sslon;
		sslon<<i;
		sslon>>strlon;
		dbcrawl.updateMysql_cookies("csdn.net", strlon, "mxj9945", ".csdn.net", "/", "all", 1, "Thu, 14-Sep-2016 03:06:23 GMT", "Thu, 14-Sep-2017 03:06:23 GMT");
	}
	//dbcrawl.updateMysql_cookies("csdn.net", "", "mxj9945", ".csdn.net", "/", "all", 1, "Thu, 14-Sep-2016 03:06:23 GMT", "Thu, 14-Sep-2017 03:06:23 GMT");
	//dbcrawl.updateMysql_cookies("csdn.net", "UN", "mxj9945", ".csdn.net", "/", "all", 1, "Thu, 14-Sep-2016 03:06:23 GMT", "Thu, 14-Sep-2017 03:06:23 GMT");
	//dbcrawl.updateMysql_cookies("www.csdn.net", "UN", "mxj9945", ".csdn.net", "/", "all", 1, "Thu, 14-Sep-2016 03:06:23 GMT", "Thu, 14-Sep-2017 03:06:23 GMT");
	//dbcrawl.deleteMysql_cookies("csdn.net");
	vector< vector<string> > cookies = dbcrawl.SelectMysql_cookies("www.csdn.net");
	cout<<cookies[0][0]<<endl;
	cout<<cookies[0][1]<<endl;
	cout<<cookies[0][2]<<endl;
}

int main(int argc,  char* argv[])
{
	testmysql();
	return 0;
}
