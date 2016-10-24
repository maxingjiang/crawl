//包含zmq的头文件 
#include "crawlstruct.h"
#include "testurls.h"

using namespace std;


int main(int argc, char * argv[])
{
	time_t tt = time(NULL);
	tm* t1= localtime(&tt);
	char time1[100];
	sprintf(time1, "%d-%02d-%02d %02d:%02d:%02d\n", t1->tm_year + 1900,t1->tm_mon + 1,t1->tm_mday,t1->tm_hour,t1->tm_min,t1->tm_sec);

	CCrawlStruct cr;
	string dataword = "@HTTP#";
	string keyword = "http";
	//string url = "http://apollo.zhixingbus.com/api/query_roads_by_station_id/279";
	//string url = "https://www.douban.com/";
	//string url = "http://weibo.com/u/1836735784/home?wvr=5";
	//string url = "http://tianya.cn/";
	string url = "https://www.baidu.com/";
	//string url = "http://news.163.com/";
	//string url = "http://bbs.tianya.cn/post-stocks-1695747-1.shtml";
	//string url = "http://home.jd.com/";
	//string url = "https://www.zhihu.com/topics";
	//string url = "http://d31.97you.net/download/%E8%A5%BF%E9%97%A8%E5%AD%90S7200_31@14333.exe";
	cr.init(url, 10000, keyword);
	cr.getUsefulUrl();
	/*CGetUrlBody body;
	body.init(url);
	body.run();*/
	//Ctesturl testcr;
	//testcr.testUrl();
	cout<<"=========main==========\n";

	time_t tt2 = time(NULL);
	tm* t2= localtime(&tt2);
	char time2[100];
	sprintf(time2, "%d-%02d-%02d %02d:%02d:%02d\n", t2->tm_year + 1900,t2->tm_mon + 1,t2->tm_mday,t2->tm_hour,t2->tm_min,t2->tm_sec);
	cout<<"begin time:"<<time1<<endl;
	cout<<"end   time:"<<time2<<endl;
	exit(0);
}
