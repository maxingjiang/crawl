/*
 * CHtmlNode.h
 *
 *  Created on: Jul 7, 2016
 *      Author: root
 */

#ifndef GUMBOSERVER_INCLUDE_REGEXSRC_H_
#define GUMBOSERVER_INCLUDE_REGEXSRC_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "gumboServer.h"
#include <gumbo.h>

using namespace std;

class HtmlNode
{
public:
	HtmlNode();
	virtual ~HtmlNode();
	string m_tag;
    map<string,string> m_attributes;
    vector<string> m_value;

	HtmlNode *m_parent;
	vector<HtmlNode*> m_child;

    string getNodeText();

};

class CHtmlNode
{
public:
	CHtmlNode();
	virtual ~CHtmlNode();

    //Parse and copy date to m_node list from Gumbo tree
    int getNodeData(const string &body);

    //Printf All node and node information
    void printfNodeList();


private:
    void getdata(HtmlNode *phtmlnode, GumboNode *gnode);//Copy date to m_node list from Gumbo tree
    void insertNodeData(HtmlNode *phtmlnode, GumboNode *gnode, GumboAttribute *attr);//Add a node to m_node list
    void printfNode(HtmlNode* htmlNode);
    void printfMapAttr(map<string,string> &attr);
	string getTag(GumboTag tag);
    void deleteHtmlNode(HtmlNode *node);


public:
	HtmlNode *m_node;
};

#endif /* GUMBOSERVER_INCLUDE_REGEXSRC_H_ */
