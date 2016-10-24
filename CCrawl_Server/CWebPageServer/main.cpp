#include <iostream>
#include <sstream>
#include "CCollectorManager.h"

using namespace std;


void testThreadMgr()
{
    ClogCPP log;
    log.init();
    string url1 = "http://news.ifeng.com/a/20160920/49993452_0.shtml";
    string url2 = "http://news.ifeng.com/a/20160921/49999495_0.shtml";
    string url3 = "http://news.ifeng.com/a/20160920/49993497_0.shtml";
    string url4 = "http://news.ifeng.com/a/20160919/49987873_0.shtml";
    string url5 = "http://news.ifeng.com/a/20160919/49987669_0.shtml";
    string url6 = "http://news.ifeng.com/a/20160923/50012641_0.shtml";
    string url7 = "http://news.ifeng.com/a/20160923/50012688_0.shtml";
    string url8 = "http://news.ifeng.com/a/20160922/50006056_0.shtml";
//    string url9 = "http://news.ifeng.com/a/20160921/49999495_0.shtml";
//    string url10 = "http://news.ifeng.com/a/20160921/49999495_0.shtml";

    CCollectorManager collectorMgr;
    int statusCode = 0;

    statusCode = collectorMgr.CreateCollectorMission(url1);
    if(statusCode != 0)
    {
        cout << "statusCode:" << statusCode << " ====Insert Task Faild!!!!" << endl;
    }
    statusCode = collectorMgr.CreateCollectorMission(url2);
    if(statusCode != 0)
    {
        cout << "statusCode: " << statusCode << " ====Insert Task Faild!!!!" << endl;
    }
    statusCode = collectorMgr.CreateCollectorMission(url3);
    if(statusCode != 0)
    {
        cout << "statusCode:" << statusCode << " ====Insert Task Faild!!!!" << endl;
    }
//    statusCode = collectorMgr.CreateCollectorMission(url4);
//    if(statusCode != 0)
//    {
//        cout << "statusCode:" << statusCode << " ====Insert Task Faild!!!!" << endl;
//    }
//    statusCode = collectorMgr.CreateCollectorMission(url5);
//    if(statusCode != 0)
//    {
//        cout << "statusCode:" << statusCode << " ====Insert Task Faild!!!!" << endl;
//    }
//    statusCode = collectorMgr.CreateCollectorMission(url6);
//    if(statusCode != 0)
//    {
//        cout << "statusCode:" << statusCode << " ====Insert Task Faild!!!!" << endl;
//    }
//    statusCode = collectorMgr.CreateCollectorMission(url7);
//    if(statusCode != 0)
//    {
//        cout << "statusCode:" << statusCode << " ====Insert Task Faild!!!!" << endl;
//    }
//    statusCode = collectorMgr.CreateCollectorMission(url8);
//    if(statusCode != 0)
//    {
//        cout << "statusCode:" << statusCode << " ====Insert Task Faild!!!!" << endl;
//    }

    sleep(1);
    int stopModel = 2;
    collectorMgr.StopAllCollectorMission(stopModel);

}

void testOneHtml()
{
//    struct stat buf;
//    FILE *fp;
//    char *data;
//    // 读取HTML文本文件
//    const char *filename = "testChild.html";
//    if(!(fp=fopen(filename,"rb"))) return;
//    stat(filename,&buf);
//    data=(char *)malloc(sizeof(char)*(buf.st_size+1));
//    fread(data,sizeof(char),buf.st_size,fp);
//    fclose(fp);
//    data[buf.st_size]=0;
//    string body = data;
//    free(data);

//    ClogCPP log;
//    log.init();

//    CCollectorManager collectorMgr;
//    CCollector* collector = NULL;

//    collector = collectorMgr.CreateCollector();

//    CWebPage* webpage = new CWebPage();
//    collector->m_webPageList.push_back(webpage);
//    webpage->SetPageCode(body);

//    webpage->Parse();

//    /*Get Rule from RuleMgr*/
//    collector->GetRuleManager()->MatchRule(webpage,1,"./testHtmlRule.txt");

//    //collector->GetRuleInterpreter()->ExtractArticles(webpage);
}

int main(void)
{
    testThreadMgr();

	return 0;
}
