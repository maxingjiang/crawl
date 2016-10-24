#pragma once
#include "CRule.h"
#include "CHtmlNode.h"

class CWebPage;

//解释器
class CRuleInterpreter
{
public:
	/*登录*/
	/*注册*/
	/*脚本解析*/

public:
	/*提取接口*/
	int ExtractTitle();
	int ExtractLoginName();
	int ExtractArticlesType();
	int ExtractUrl();
    int ExtractArticles(CWebPage* webPage);
    int ExtractNextPageUrl(CRuleItem &Rule, HtmlNode* root_node, string &nextPageUrl);

    //Return a html page title
    string findTitle(HtmlNode* root_node);

    //Return all url of a html page code to a vector
    void getAllUrl(vector<string> &url, HtmlNode* root_node);

private:
    int findTag(CTag &tag, HtmlNode *node, HtmlNode **resultNode);

    int ExtractNode(CRuleItem &Rule, HtmlNode* root_node, HtmlNode **validAreaNode);

    void printfMapAttr(map<string,string> &attr);
    void printfNode(HtmlNode *htmlNode, string& printValue);

    //
    void getUrlFromNode(vector<string> &url, HtmlNode* node);


};
