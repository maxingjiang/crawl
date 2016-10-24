#include "CInterpreter.h"
#include "CWebPage.h"


int CRuleInterpreter::ExtractTitle()
{
	return 0;

}

int CRuleInterpreter::ExtractLoginName()
{
	return 0;

}

int CRuleInterpreter::ExtractArticlesType()
{
	return 0;

}

int CRuleInterpreter::ExtractUrl()
{
	return 0;

}
int CRuleInterpreter::findTag(CTag &tag, HtmlNode *node, HtmlNode **resultNode)
{
    int count = 0;
    bool flag = true;

    for(unsigned int i = 0; i < node->m_child.size(); i++)
    {
        HtmlNode* childNode = node->m_child[i];

        if(childNode->m_tag == tag.m_tag)
        {
            if(tag.m_attributes.size() > 0)
            {
                map<string,string>::iterator nodeIter;
                for(nodeIter = childNode->m_attributes.begin(); nodeIter != childNode->m_attributes.end(); nodeIter++)
                {
                    flag = false;
                    map<string,string>::iterator tagIter;
                    tagIter = tag.m_attributes.find(nodeIter->first);
                    if(tagIter == tag.m_attributes.end())
                    {
                        continue;
                    }
                    else
                    {
                        if(tagIter->second == nodeIter->second)
                        {
                            flag = true;
                            break;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }

            if(flag == true)
            {
                count++;
                *resultNode = childNode;
                if(tag.m_count == count)
                {
                    return 0;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
    }
    return 1;
}
int CRuleInterpreter::ExtractNode(CRuleItem &Rule, HtmlNode* root_node, HtmlNode **resultNode)
{
    if(!root_node)
        return 1;

    HtmlNode* node = root_node;
    *resultNode = root_node;

    vector<CObtainCode> &obtainCode = Rule.m_obtainCode;

    if(obtainCode.size() <= 0)
        return 2;

    for (unsigned int i = 0; i < obtainCode.size(); i++)
    {
        CObtainCode unitObtainCode;
        unitObtainCode = obtainCode[i];

        vector<CTag> &tagList = unitObtainCode.m_tagList;

        for (unsigned int j = 0; j < tagList.size(); j++)
        {
            CTag tag = tagList[j];

            if(findTag(tag, node, &node) == 0)
            {
                 *resultNode = node;
            }
            else
            {
                cout << "-----------Can not find Tag: <" << tag.m_tag;
                map<string,string>::iterator tagIter;
                for(tagIter = tag.m_attributes.begin(); tagIter != tag.m_attributes.end(); tagIter++)
                {
                    cout << " " << tagIter->first << "=\"";
                    cout << tagIter->second << "\"";
                }
                cout << ">" << endl;
                return 3;
            }
        }
    }
    return 0;
}

int CRuleInterpreter::ExtractArticles(CWebPage* webPage)
{
    if(!webPage)
        return 1;
    if(!webPage->m_pageRule)
        return 2;
    HtmlNode* validAreaNode = NULL;
    HtmlNode* titleNode = NULL;
    HtmlNode* contentNode = NULL;
    string printValue;

    CArticle article;

    int returnCode = 0;

     /*///////////////////////////----ValidArea----////////////////////////////////*/
    returnCode = ExtractNode(webPage->m_pageRule->m_validArea,webPage->m_htmlNode.m_node,&validAreaNode);

    if(returnCode == 0)
    {
         /*////////////////////////////----title----///////////////////////////////*/
        returnCode = ExtractNode(webPage->m_pageRule->m_titleRule,validAreaNode,&titleNode);
        if(returnCode == 0)
        {
            printValue = "";
            printfNode(titleNode, printValue);

            article.SetTitle(printValue);

        }
        else if(returnCode == 1)
        {
            cout << "Title Node is empty!" << endl;
        }
        else if(returnCode == 2)
        {
            printValue = "<Title is empty>";
            cout << "Title Rule is Null!" << endl;
            cout << printValue << endl;
        }

        /*/////////////////////////----content----//////////////////////////////////*/
        returnCode = ExtractNode(webPage->m_pageRule->m_contentRule,validAreaNode,&contentNode);
        if(returnCode == 0)
        {
            printValue = "";
            printfNode(contentNode, printValue);

            article.SetContent(printValue);
        }
        else if(returnCode == 1)
        {
            cout << "Content Node is empty!" << endl;
        }
        else if(returnCode == 2)
        {
            printValue = "<Content is empty>";
            cout << "Content Rule is Null!" << endl;
            cout << printValue << endl;
        }

        /*/////////////////////////----nextPage----//////////////////////////////////*/
        string nextPageUrl = "";
        returnCode = ExtractNextPageUrl(webPage->m_pageRule->m_contentNextPageRule,validAreaNode,nextPageUrl);
        if(returnCode == 0)
        {
            webPage->SetNextPageUrl(nextPageUrl);
        }
        else if(returnCode == 1)
        {
            cout << "nextPage Node is empty!" << endl;
        }
        else if(returnCode == 2)
        {
            printValue = "<nextPage is empty>";
            cout << "nextPage Rule is Null!" << endl;
            cout << printValue << endl;
        }
    }
    else if(returnCode == 1)
    {
        cout << "Valid Area Node is empty!" << endl;
    }
    else if(returnCode == 2)
    {
        printValue = "" ;
        cout << "Valid area Rule is Null!" << endl;
        cout << printValue << endl;
    }

    webPage->m_articlesList.push_back(article);
    return 0;
}

int CRuleInterpreter::ExtractNextPageUrl(CRuleItem &Rule, HtmlNode* root_node, string &nextPageUrl)
{
    int returnCode = 0;
    HtmlNode* nextPageNode;

    returnCode = ExtractNode(Rule, root_node, &nextPageNode);

    if(returnCode == 0)
    {
        map<string,string>::iterator attr_it;
        for (attr_it = nextPageNode->m_attributes.begin(); attr_it != nextPageNode->m_attributes.end(); attr_it++)
        {
            if(attr_it->first == "href")
            {
                int POST_pos = attr_it->second.find("http", 0);
                if(POST_pos == 0)
                {
                    nextPageUrl = attr_it->second;
                }
                break;
            }
        }
    }

    return returnCode;
}

void CRuleInterpreter::printfMapAttr(map<string,string> &attr)
{
    map<string,string>::iterator attr_it;
    for (attr_it = attr.begin(); attr_it != attr.end(); attr_it++)
    {
        cout << attr_it->first << " = " << attr_it->second << " " << endl;
    }
}

void CRuleInterpreter::printfNode(HtmlNode *htmlNode, string& printValue)
{
    if(htmlNode == NULL)
    {
        cout << endl;
        cout << __FILE__ << __LINE__ <<" Node is empty" << endl;
        return ;
    }

    printValue = htmlNode->getNodeText();
}

void CRuleInterpreter::getAllUrl(vector<string> &url, HtmlNode* root_node)
{
    getUrlFromNode(url,root_node);
}

void CRuleInterpreter::getUrlFromNode(vector<string> &url, HtmlNode* node)
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

string CRuleInterpreter::findTitle(HtmlNode* root_node)
{
    HtmlNode* node = root_node;
    HtmlNode* child = NULL;
    HtmlNode* head = NULL;

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


































