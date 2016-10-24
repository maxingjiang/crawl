#include <iostream>
#include <string>
#include <sys/stat.h>
#include <stdlib.h>
#include "gumboServer.h"
#include "CHtmlNode.h"
#include "CHtmlParseInterface.h"
#include "callpy.h"

using namespace std;

int testweibo_unicode()
{
	 struct stat buf;
	 FILE *fp;
	 char *data;
	 // 读取HTML文本文件
     const char *filename = "weibo.html";
	 if(!(fp=fopen(filename,"rb"))) return -1;
	 stat(filename,&buf);
	 data=(char *)malloc(sizeof(char)*(buf.st_size+1));
	 fread(data,sizeof(char),buf.st_size,fp);
	 fclose(fp);
	 data[buf.st_size]=0;
	 string body = data;
	 free(data);

     CHtmlNode node;
     node.getNodeData(body);
     node.printfNodeList();

     return 0;
}

int testHtmlNode()
{
	 struct stat buf;
	 FILE *fp;
	 char *data;
	 // 读取HTML文本文件
     const char *filename = "zx.html";
	 if(!(fp=fopen(filename,"rb"))) return -1;
	 stat(filename,&buf);
	 data=(char *)malloc(sizeof(char)*(buf.st_size+1));
	 fread(data,sizeof(char),buf.st_size,fp);
	 fclose(fp);
	 data[buf.st_size]=0;
	 string body = data;
	 free(data);

     CHtmlParseInterface parseInterface;
     CHtmlNode node;
     node.getNodeData(body);

     vector<string> url;
     parseInterface.getAllUrl(url,node.m_node);

     for(unsigned int i = 0; i < url.size(); i++)
     {
         cout << "Url: " << url[i] <<endl;
     }

     return 0;
}

int testChildNodeBug()
{
     struct stat buf;
     FILE *fp;
     char *data;
     // 读取HTML文本文件
     const char *filename = "testChild.html";
     if(!(fp=fopen(filename,"rb"))) return -1;
     stat(filename,&buf);
     data=(char *)malloc(sizeof(char)*(buf.st_size+1));
     fread(data,sizeof(char),buf.st_size,fp);
     fclose(fp);
     data[buf.st_size]=0;
     string body = data;
     free(data);

     CHtmlNode node;
     node.getNodeData(body);
     cout<<"================\n\n\n\n";
     node.printfNodeList();

     return 0;
}

int main()
{
    testChildNodeBug();
	return 0;
}



