#include <iostream>
#include "CWebPage.h"
using namespace std;

int CWebPage::WebPageId = -1;

CWebPage::CWebPage()
{
    m_webPageId = ++WebPageId;
    m_webPageStatus = WEBPAGE_STATUS_READY;
	m_title = "";
	m_loginName = "";
	m_url = "";
	m_nextPageUrl = "";
	m_articleType = SOURCECODE;
	m_articlesList.clear();
	m_pageCode = "";
	m_pageRule = NULL;
}

CWebPage::CWebPage(string pageUrl)
{
    m_webPageId = ++WebPageId;
    m_webPageStatus = WEBPAGE_STATUS_READY;
    m_title = "";
    m_loginName = "";
    m_url = pageUrl;
    m_nextPageUrl = "";
    m_articleType = SOURCECODE;
    m_articlesList.clear();
    m_pageCode = "";
    m_pageRule = NULL;
}

CWebPage::CWebPage(int webPageId, string pageUrl)
{
    m_webPageId = webPageId;
    m_webPageStatus = WEBPAGE_STATUS_READY;
	m_title = "";
	m_loginName = "";
	m_url = pageUrl;
	m_nextPageUrl = "";
	m_articleType = SOURCECODE;
	m_articlesList.clear();
	m_pageCode = "";
	m_pageRule = NULL;
}

CWebPage::CWebPage(string pageUrl,string pageCode)
{
    m_webPageId = ++WebPageId;
    m_webPageStatus = WEBPAGE_STATUS_READY;
	m_title = "";
	m_loginName = "";
	m_url = pageUrl;
	m_nextPageUrl = "";
	m_articleType = SOURCECODE;
	m_articlesList.clear();
	m_pageCode = pageCode;
	m_pageRule = NULL;
}

CWebPage::CWebPage(string pageUrl, CRule* pageRuel)
{
    m_webPageId = ++WebPageId;
    m_webPageStatus = WEBPAGE_STATUS_READY;
	m_title = "";
	m_loginName = "";
	m_url = pageUrl;
	m_nextPageUrl = "";
	m_articleType = SOURCECODE;
	m_articlesList.clear();
	m_pageCode = "";
	m_pageRule = pageRuel;
}

CWebPage::CWebPage(string pageUrl, string pageCode, CRule* pageRuel)
{
    m_webPageId = ++WebPageId;
    m_webPageStatus = WEBPAGE_STATUS_READY;
	m_title = "";
	m_loginName = "";
	m_url = pageUrl;
	m_nextPageUrl = "";
	m_articleType = SOURCECODE;
	m_articlesList.clear();
	m_pageCode = pageCode;
	m_pageRule = pageRuel;
}

CWebPage::~CWebPage()
{
    if(m_pageRule)
        delete m_pageRule;
}

bool CWebPage::AddArticle(const CArticle &article)
{
	try
	{
		m_articlesList.push_back(article);
	}
	catch (int id)
	{
		cout << "Exception:" << id << endl;
		return false;
	}
	catch (out_of_range &e)
	{
		cout << "an exception of out_of_range:" << e.what() << endl;
		return false;
	}
	catch (bad_alloc &e)
	{
		cout << "an exception of an unexpected type:" << e.what() << endl;
		return false;
	}
	return true;
}

bool CWebPage::IsArticleEmpty()
{
	return m_articlesList.empty();
}

bool CWebPage::DeleteArticle(CArticle article)
{
	try
	{
		for (vector<CArticle>::size_type i = 0;i < m_articlesList.size();i++)
		{
			if (m_articlesList[i] == article)
			{
				m_articlesList.erase(m_articlesList.begin() + i);
			}
		}
	}
	catch (int id)
	{
		cout << "Exception:" << id << endl;
		return false;
	}
	catch (out_of_range &e)
	{
		cout << "an exception of out_of_range:" << e.what() << endl;
		return false;
	}
	catch (bad_alloc &e)
	{
		cout << "an exception of an unexpected type:" << e.what() << endl;
		return false;
	}
	return true;
}

bool CWebPage::ClearArticle()
{
	try
	{
		m_articlesList.clear();
	}
	catch (int id)
	{
		cout << "Exception:" << id << endl;
		return false;
	}
	catch (out_of_range &e)
	{
		cout << "an exception of out_of_range:" << e.what() << endl;
		return false;
	}
	catch (bad_alloc &e)
	{
		cout << "an exception of an unexpected type:" << e.what() << endl;
		return false;
	}
	return true;
}
void CWebPage::AddChildUrl(vector<string>& urls)
{
     m_childUrl.insert(m_childUrl.end(),urls.begin(),urls.end());
}

void CWebPage::GetChildUrls(vector<string>& urls)
{
    urls = m_childUrl;
}

int CWebPage::Parse()
{
    m_htmlNode.getNodeData(m_pageCode);
    ParseTitle();
    GetAllUrl();
    return 0;
}

int CWebPage::ParseTitle()
{
    m_title = m_ruleInterpreter.findTitle(m_htmlNode.m_node);
    return 0;
}

int CWebPage::GetAllUrl()
{
    m_ruleInterpreter.getAllUrl(m_childUrl,m_htmlNode.m_node);
    return 0;
}
