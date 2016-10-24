/*
 * CHtmlParseInterface.cpp
 *
 *  Created on: Aug 18, 2016
 *      Author: root
 */

#include "CHtmlParseInterface.h"

CHtmlParseInterface::CHtmlParseInterface()
{
	// TODO Auto-generated constructor stub

}

CHtmlParseInterface::~CHtmlParseInterface()
{
	// TODO Auto-generated destructor stub
}

string CHtmlParseInterface::findTitle(HtmlNode* root_node)
{
    HtmlNode* node = root_node;
    HtmlNode* child = NULL;
    HtmlNode* head = NULL;

    string title = "";

    for (unsigned int i = 0; i < node->m_child.size(); ++i)
    {
        child = node->m_child[i];
        if (child->m_tag == "head")
        {
            head = child;
            break;
        }
    }

    if (!head)
    {
        return "<title empty>";
    }

    for (unsigned int i = 0; i < head->m_child.size(); ++i)
    {
        child = head->m_child[i];
        if (child->m_tag == "title")
        {

            return child->getNodeText();
        }
    }
    return "<title empty>";
}

void CHtmlParseInterface::getUrlFromNode(vector<string> &url, HtmlNode* node)
{
    if (!node)
    {
        return ;
    }

    if (node->m_tag == "a")
    {
        //vector<map<string,string> > attr = node->m_attributes;
        map<string,string> &attrMapUnit = node->m_attributes;

        map<string,string>::iterator attrMapUnit_it;
        for (attrMapUnit_it = attrMapUnit.begin(); attrMapUnit_it != attrMapUnit.end(); attrMapUnit_it++)
        {
           if(attrMapUnit_it->first == "href")
           {
               vector<string>::iterator ret;
               ret = std::find(url.begin(), url.end(), (string)attrMapUnit_it->second);
               if(ret == url.end())
               {
                   int POST_pos = attrMapUnit_it->second.find("http", 0);
                   if(POST_pos == 0)
                   {
                       url.push_back(attrMapUnit_it->second);
                   }
               }
           }
        }
    }

    HtmlNode* child = NULL;
    for (unsigned int i = 0; i < node->m_child.size(); ++i)
    {
        child = node->m_child[i];
        getUrlFromNode(url,child);
    }
}

void CHtmlParseInterface::getAllUrl(vector<string> &url, HtmlNode* root_node)
{
    getUrlFromNode(url,root_node);
}

