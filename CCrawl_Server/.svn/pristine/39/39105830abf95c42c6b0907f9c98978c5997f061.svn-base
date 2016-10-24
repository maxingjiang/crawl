/*
 * crawlstruct.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: root
 */

#include <string.h>
#include "crawlstruct.h"

#include "CCrawlManager.h"
#include "common.h"
#include "log4cpp.h"
#include "split.h"
#include "gumboServer.h"
#include "CHtmlNode.h"

void CCrawlStruct::init(string url, int urlnum, string keyword)
{
	m_url_index = 0;
	m_url_nums = urlnum;
	m_keyword.clear();
	m_allproxyip.clear();
	m_keyword = keyword;
	m_allurl.push_back(url);
    ClogCPP log;
    log.init();
}

void CCrawlStruct::clear()
{
	m_keyword = "";
	m_allproxyip.clear();
}

void CCrawlStruct::getUsefulUrl()
{

	string cmd = string("echo \"\" > ./a.txt");
	system(cmd.c_str());
	string body;
	//int keykord_index = 0;
    char src[1024] = {0x00};

	CCrawlManager crmanager;
	CCrawl crawl;
	string url;
	while(m_allurl.size() < m_url_nums && m_url_index < m_allurl.size())
	{
		cout<<m_allurl.size()<<":"<<m_url_nums<<": url: "<<m_allurl[m_url_index]<<endl;
		cmd = string("echo \"")+m_allurl[m_url_index]+"\" >> "+"./url.conf";
		system(cmd.c_str());
		crawl.setHttpRequestInit();
		int statuscode = crawl.GET_Html(m_allurl[m_url_index], "aaa.png");
		cout<<"status code: "<<statuscode<<endl;
		string headers;
		crawl.getResponseHeaders(headers);
		//cout<<headers<<endl;
		string body;
		crawl.getResponseBody(body);
		CHtmlNode node;
		node.getNodeData(body);
		//cout<<body<<endl;
		CResponseHeaders responseHeaders;
		crawl.getResponseHeaders(responseHeaders);
		crawl.setHttpRequestCleanup();
		sprintf(src, "%d:=====>url: %s\nstatus code: %s\ntype: %s\nlocation: %s\n", m_url_index,
				url.c_str(), responseHeaders.getStatusCode().c_str(), responseHeaders.getContentType().c_str(),
				responseHeaders.getLocation().c_str());

		cmd = string("echo \"")+src+"\" >> "+"./a.txt";
		//cout<<cmd<<endl;
		system(cmd.c_str());

		m_url_index++;
		cout<<"m_allurl: "<<m_allurl.size()<<" index : "<<m_url_index<<endl;
		if(m_allurl.size() >= m_url_nums -100)
			continue;
		CgumboServer gmb;
		if(body.size() <= 0)
			continue;
		gmb.getAllInfo(body);
		getUrlLink(m_keyword, body);
		vector <string>::iterator urlsiter = m_usefulurls.begin();
		for(; urlsiter != m_usefulurls.end(); urlsiter++)
		{
			//LOG4CPLUS_DEBUG(ClogCPP::m_logger, "runPthread begin....");
			bool flag = 0;
			vector <string>::iterator iter = m_allurl.begin();
			for(; iter != m_allurl.end(); iter++)
			{
				//cout<<"*iter: "<<*iter<<endl;
				//cout<<"*urlsiter: "<<*urlsiter<<endl;
				if((*iter).compare(*urlsiter) == 0)
				{
					flag = 1; //url exit, continue
					break;
				}
			}
			if(flag == 0)
			{
				m_allurl.push_back(*urlsiter);
				string cmd = string("echo \"")+*urlsiter+"\" >> ./url.txt";
				system(cmd.c_str());
			}
			if(m_allurl.size() == m_url_nums)
			{
				cout<<m_allurl.size()<<":"<<m_url_nums<<" 86\n";
				m_allurl.pop_back();
				break ;
			}
		}
	}
}


void CCrawlStruct::getUrlLink(string &keyword, string &urldata)
{
	vector <string> usefulurls;
	GumboOutput* output = gumbo_parse(urldata.c_str());
	search_for_links(output->root);
	gumbo_destroy_output(&kGumboDefaultOptions, output);
}

void CCrawlStruct::search_for_links(GumboNode* node)
{
  if (node->type != GUMBO_NODE_ELEMENT)
  {
    return;
  }
  GumboAttribute* href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href")))
  {
	string src = href->value;
	//cout<<"src: "<<src<<endl;
	int pos = src.find(m_keyword.c_str(), 0);
	//cout<<"len: "<<strlen(href->value)<<endl;
	if(pos >= 0 && strlen(href->value) <= 512)
	{
		//std::cout <<"===use===>"<< href->value << std::endl;
		m_usefulurls.push_back(href->value);
	}
  }
  if (node->v.element.tag == GUMBO_TAG_IMG &&
        (href = gumbo_get_attribute(&node->v.element.attributes, "src")))
  {
  	string src = href->value;
  	//cout<<"========>img: "<<src<<endl;
  	/*
  	int pos = src.find("uploads", 0);
  	if(pos >= 0)
  	{
  	    string cmd = "echo "+src+" >> ./image.log";
  	    system(cmd.c_str());
  	}
  	*/
  }
  GumboVector* children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i)
  {
    search_for_links(static_cast<GumboNode*>(children->data[i]));
  }
}

void CCrawlStruct::writeProxyToFile(string pathfile)
{
	string cmd = "echo \"\" > "+pathfile;
	system(cmd.c_str());
	for(unsigned int index = 0; index < m_allproxyip.size(); index++)
	{
		string cmd = "echo "+m_allproxyip[index]+" >> "+pathfile;
		system(cmd.c_str());
	}

}


