/*
 * CHtmlParseInterface.h
 *
 *  Created on: Aug 18, 2016
 *      Author: root
 */

#ifndef GUMBOSERVER_CHTMLPARSEINTERFACE_H_
#define GUMBOSERVER_CHTMLPARSEINTERFACE_H_

#include "CHtmlNode.h"

class CHtmlParseInterface
{
public:
	CHtmlParseInterface();
	virtual ~CHtmlParseInterface();

	//Return a html page title
    string findTitle(HtmlNode* root_node);

	//Return all url of a html page code to a vector
    void getAllUrl(vector<string> &url, HtmlNode* root_node);

	//Return parent node
	HtmlNode* getParentNode(HtmlNode* node);

	//Return brother node on a vector
	vector<HtmlNode*> getBrothers(HtmlNode* node);

	//Return node child vector from a node
	vector<HtmlNode*> getChildList(HtmlNode* node);

private:
    void getUrlFromNode(vector<string> &url, HtmlNode* node);
};

#endif /* GUMBOSERVER_CHTMLPARSEINTERFACE_H_ */
