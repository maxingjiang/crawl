#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "CCrawlManager.h"
#include "insertRequestHeadersData.h"
#include "postLogin.h"
#include "CCookie.h"
#include "Encode.h"

using namespace std;

string getfile(const string &filename)
{
	 struct stat buf;
	 FILE *fp;
	 char *data;
	 // 读取HTML文本文件
	 if(!(fp=fopen(filename.c_str(),"rb"))) return "";
	 stat(filename.c_str(),&buf);
	 data=(char *)malloc(sizeof(char)*(buf.st_size+1));
	 fread(data,sizeof(char),buf.st_size,fp);
	 fclose(fp);
	 data[buf.st_size]=0;
	 string body = data;
	 free(data);
	 return body;
}

void testmysql()
{
	string host = "127.0.0.1";
	string user = "root";
	string pass = "123456";
	string dbname = "crawldb";
	int poolSize = 10;
	CDBServer crawl;
	crawl.initMysqlPool(host,user,pass,dbname,poolSize);
	Connection* connect = crawl.getConnection();

	if(!connect){
		cout << "getConnection NULL pointer" << endl;
		exit(-1);
	}

	CinsertRequestHeadersData insertdata;
	insertdata.m_dbcrawl = crawl;
	/*insertdata.insert_default_data();
	insertdata.insert_tianya_data();
	insertdata.insert_douban_data();
	insertdata.insert_zhihu_data();
	insertdata.insert_csdn_data();
	insertdata.insert_weibo_data();
	insertdata.insert_proxy_data();*/
	insertdata.insert_requestHeaders_to_db_from_file("a.conf");
	crawl.releaseConnection();
	crawl.destroyMysqlPool();
}

void testGetResponseData()
{

	CCrawlManager crmanager;
	CCrawl *crawl = crmanager.createCrawl();
	int num = 10;
	while(num--)
	{
		crawl->setHttpRequestInit();
		CRequestHeaders requestHeaders;//set
		crawl->setRequestHeaders(requestHeaders);
		CProxy proxy;//set
		crawl->setProxy(proxy);

		//int statuscode = crawl->POST_Html(loginurl, postdata);

		//int statuscode = crawl->GET_Html("http://s.weibo.com/weibo/%25E9%2599%2588%25E8%25B5%25AB?topnav=1&wvr=6&b=1", "aaa.png");
		int statuscode = crawl->GET_Html("http://blog.csdn.net/a854073071/article/details/52856797", "aaa.png");
		cout<<"status code: "<<statuscode<<endl;
		string headers;
		crawl->getResponseHeaders(headers);
		cout<<headers<<endl;
		string body;
		crawl->getResponseBody(body);
		crawl->setHttpRequestCleanup();

		CCookie c;
		c.setWebsite("www.baidu.com");
		c.getCookie(1);
		string keyvalue;
		c.getCookieKeyValue(keyvalue);
		cout<<"cookie====>: "<<keyvalue<<endl;
		//cout<<"\n\n\n\n\n"<<body<<endl;
	}
	crmanager.deleteCrawl(crawl);
	//cout<<body<<endl;

}

int teststringhtml()
{
	 struct stat buf;
	 FILE *fp;
	 char *data;

	 /* 读取HTML文本文件 */
	 const char *filename = "zx.html";
	 if(!(fp=fopen(filename,"rb")))
		 return -1;
	 stat(filename,&buf);
	 data=(char *)malloc(sizeof(char)*(buf.st_size+1));
	 fread(data,sizeof(char),buf.st_size,fp);
	 fclose(fp);
	 data[buf.st_size]=0;
	 string responsedata = data;
	 for(int i = 0; i < responsedata.size(); i++)
		 cout<<responsedata[i];
	 cout<<endl<<data<<endl;
	 free(data);
	 CcharsetEncode charset;
	 charset.unicode_to_utf8(responsedata);
	 cout<<responsedata<<endl;
	 return 0;
}

int testLogin()
{

	CCrawlManager crmanager;
	CCrawl *crawl = crmanager.createCrawl();
	crawl->setHttpRequestInit();
	CRequestHeaders requestHeaders;//set

	crawl->setRequestHeaders(requestHeaders);
	CProxy proxy;//set
	crawl->setProxy(proxy);

	string loginurl = "http://192.168.40.200/home.php?mod=spacecp&ac=profile&op=edu";
	string postdata = getfile("data.txt");
	cout<<postdata<<endl;
	CPostLogin clogin;
	clogin.login(crawl, loginurl, postdata);
	int status;
	string headers;
	crawl->getResponseHeaders(headers);
	cout<<headers<<endl;
	string body;
	crawl->getResponseBody(body);
	cout<<body<<endl;

	crawl->setHttpRequestCleanup();

	return status;
}

int multipart()
{

	CCrawlManager crmanager;
	CCrawl *crawl = crmanager.createCrawl();
	crawl->setHttpRequestInit();
	CRequestHeaders requestHeaders;//set

	crawl->setRequestHeaders(requestHeaders);
	CProxy proxy;//set
	crawl->setProxy(proxy);

	string url = "http://220.197.219.187/home.php?mod=spacecp&ac=profile&op=work";
	int statuscode = crawl->GET_Html(url, "aaa.png");
	cout<<"status code: "<<statuscode<<endl;
	string headers, bodys;
	crawl->getResponseHeaders(headers);
	crawl->getResponseBody(bodys);
	cout<<headers<<endl;
	CPPregex regex;
	string logindata;
	regex.getCharset(bodys, logindata, "name=\"formhash\" value=\"(.*?)\"");
	crawl->setHttpRequestCleanup();
	crawl->setHttpRequestInit();
	map<string, string> postdata;
	postdata.insert(pair<string,string>("formhash",logindata));

	postdata.insert(pair<string,string>("company", "cumt123"));
	postdata.insert(pair<string,string>("privacy[company]", "0"));
	postdata.insert(pair<string,string>("occupation", "it"));
	postdata.insert(pair<string,string>("privacy[occupation]", "0"));
	postdata.insert(pair<string,string>("position", "kf3"));
	postdata.insert(pair<string,string>("privacy[position]", "0"));
	postdata.insert(pair<string,string>("revenue", "20"));
	postdata.insert(pair<string,string>("privacy[revenue]", "0"));
	postdata.insert(pair<string,string>("profilesubmit", "true"));
	postdata.insert(pair<string,string>("profilesubmitbtn", "true"));

	crawl->POST_multipart_Html(url, postdata);
	crawl->getResponseHeaders(headers);
	cout<<headers<<endl;
	string body;
	crawl->getResponseBody(body);
	//cout<<body<<endl;

	crawl->setHttpRequestCleanup();

	return statuscode;
}

void testdiscuzget(const string &url, string &logindata)
{

	CCrawlManager crmanager;
	CCrawl *crawl = crmanager.createCrawl();

	crawl->setHttpRequestInit();
	CRequestHeaders requestHeaders;//set
	CReferer referer;
	referer.setReferer("Referer: http://192.168.40.200/forum.php?mod=post&action=newthread&fid=2");
	requestHeaders.setReferer(referer);
	crawl->setRequestHeaders(requestHeaders);
	int statuscode = crawl->GET_Html(url, "aaa.png");
	cout<<"status code: "<<statuscode<<endl;
	string headers, bodys;
	crawl->getResponseHeaders(headers);
	crawl->getResponseBody(bodys);
	cout<<headers<<endl;
	CPPregex regex;
	regex.getCharset(bodys, logindata, "name=\"formhash\" value=\"(.*?)\"");
	crawl->setHttpRequestCleanup();

	crmanager.deleteCrawl(crawl);
}

void testdiscuzpost(const string &url, const string &postdt)
{
	CCrawlManager crmanager;
	CCrawl *crawl = crmanager.createCrawl();

	crawl->setHttpRequestInit();
	CRequestHeaders requestHeaders;//set
	CReferer referer;
	referer.setReferer("Referer: http://192.168.40.200/forum.php?mod=post&action=newthread&fid=2");
	requestHeaders.setReferer(referer);
	crawl->setRequestHeaders(requestHeaders);
	cout<<"postdt: "<<postdt<<endl;
	int statuscode = crawl->POST_data_Html(url, postdt);
	cout<<"status code: "<<statuscode<<endl;
	string headers;
	crawl->getResponseHeaders(headers);
	cout<<headers<<endl;
	string body;
	crawl->getResponseBody(body);
	cout<<body<<endl;
	crawl->setHttpRequestCleanup();
	crmanager.deleteCrawl(crawl);
}

void logindiscuz()
{
	string logindata, data;
	testdiscuzget("http://192.168.40.200/forum.php?mod=post&action=newthread&fid=2", logindata);
	cout<<"====================>"<<logindata<<endl;
	testdiscuzget("http://192.168.40.200/home.php?mod=misc&ac=sendmail&rand=1476768899", data);
	testdiscuzget("http://192.168.40.200/member.php?mod=logging&action=login&infloat=yes&frommessage&inajax=1&ajaxtarget=messagelogin", data);
	data = string("formhash=")+logindata+"&referer=http%3A%2F%2F220.197.219.187%2Fforum.php%3Fmod%3Dpost%26action%3Dnewthread%26fid%3D2&loginfield=username&username=mxj&password=123456&questionid=0&answer=&loginsubmit=true";
	testdiscuzpost("http://192.168.40.200/member.php?mod=logging&action=login&loginsubmit=yes&frommessage&loginhash=LMZ5s&inajax=1", data); //login
	testdiscuzget("http://192.168.40.200/forum.php?mod=post&action=newthread&fid=2", logindata);
	cout<<"logindata: ======>"<<logindata<<endl;
	string subject = "我的第一个discuz";
	string message = "我的第一个discuz我的第一个discuz";
	CEncode encode;
	string subject_encode, message_encode;
	//utf-8
	//encode.URLEncode(subject_encode, subject);
	//encode.URLEncode(message_encode, message);
	//gbk
	/*CcharsetEncode cencode;
	cencode.charset(subject, subject_encode, "utf-8", "GBK");
	cencode.charset(message, message_encode, "utf-8", "GBK");*/
	CcharsetEncode cencode;
	cencode.charset(subject, subject_encode, "utf-8", "big5");
	cencode.charset(message, message_encode, "utf-8", "big5");

	data = string("formhash=")+logindata+"&posttime=1476942970&wysiwyg=1&subject="+subject_encode+"&message="+message_encode+"%0D%0A&allownoticeauthor=1&usesig=1&save=";
	testdiscuzpost("http://192.168.40.200/forum.php?mod=post&action=newthread&fid=2&extra=&topicsubmit=yes", data);//publish

}

int main(int argc,  char* argv[])
{
	//ClogCPP log;
	//log.init();
	//testmysql();
	//testGetResponseData();
	//teststringhtml();
	//testLogin();
	//multipart();
	logindiscuz();

	return 0;
}
