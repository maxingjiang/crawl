#pragma once

#include "CArticle.h"
#include "CCrawl.h"
#include "CInterpreter.h"

#define WEBPAGE_STATUS_READY    1
#define WEBPAGE_STATUS_RUNNING  2
#define WEBPAGE_STATUS_COMPLETE 3

//网页类
class CWebPage
{
private:
    static int WebPageId;

    int m_webPageId;
    int m_webPageStatus;

	string m_title;				//网页标题
	string m_loginName;			//登录名
	string m_url;				//网页链接
	string m_nextPageUrl;		//下一页连接
    string m_refererUrl;		//
    vector<string> m_childUrl;  //childUrl
	int m_articleType;			//文章类型
	string m_pageCode;			//网页源码

public:
    vector<CArticle> m_articlesList;//文章内容
	CRule* m_pageRule;			//网页规则
	CCrawl* m_crawl;
    CHtmlNode m_htmlNode;
    CRuleInterpreter m_ruleInterpreter;

public:
	CWebPage();
	CWebPage(string pageUrl);
    CWebPage(int webPageId, string pageUrl);
	CWebPage(string pageUrl, string pageCode);
	CWebPage(string pageUrl, CRule* pageRuel);
	CWebPage(string pageUrl, string pageCode, CRule* pageRuel);
	virtual ~CWebPage();

public:
    void SetWebPageId(int webpageId);
    int GetWebPageId();

    void SetWebPageStatus(int webpageStatus);
    int GetWebPageStatus();

	void SetTitle(string title);
	string GetTitle();

	void SetLoginName(string loginName);
	string GetLoginName();

	void SetUrl(string url);
	string GetUrl();

	void SetNextPageUrl(string nextPageUrl);
	string GetNextPageUrl();

	void SetRefererUrl(string refererUrl);
	string GetRefererUrl();

    void AddChildUrl(vector<string>& urls);
    void GetChildUrls(vector<string>& urls);

	void SetArticleType(int articleType);
	int GetArticleType();

	void SetPageCode(string &pageCode);
	string GetPageCode();

	void SetPageRule(CRule *pageRule);
	CRule* GetPageRule();

public:
	bool AddArticle(const CArticle &article);
	CArticle GetArticle();
	bool IsArticleEmpty();
	bool DeleteArticle(CArticle article);
	bool ClearArticle();

public:
    int Parse();
    int ParseTitle();
    int GetAllUrl();
};

inline void CWebPage::SetWebPageId(int webpageId)
{
    m_webPageId = webpageId;
}

inline int CWebPage::GetWebPageId()
{
    return m_webPageId;
}

inline void CWebPage::SetWebPageStatus(int webpageStatus)
{
    m_webPageStatus = webpageStatus;
}

inline int CWebPage::GetWebPageStatus()
{
    return m_webPageStatus;
}

inline void CWebPage::SetTitle(string title)
{
	m_title = title;
}

inline string CWebPage::GetTitle()
{
	return m_title;
}

inline void CWebPage::SetLoginName(string loginName)
{
	m_loginName = loginName;
}

inline string CWebPage::GetLoginName()
{
	return m_loginName;
}

inline void CWebPage::SetUrl(string url)
{
	m_url = url;
}

inline string CWebPage::GetUrl()
{
	return m_url;
}

inline void CWebPage::SetNextPageUrl(string nextPageUrl)
{
	m_nextPageUrl = nextPageUrl;
}

inline string CWebPage::GetNextPageUrl()
{
	return m_nextPageUrl;
}

inline void CWebPage::SetRefererUrl(string refererUrl)
{
	m_refererUrl = refererUrl;
}

inline string CWebPage::GetRefererUrl()
{
	return m_refererUrl;
}

inline void CWebPage::SetArticleType(int articleType)
{
	m_articleType = articleType;
}

inline int CWebPage::GetArticleType()
{
	return m_articleType;
}

inline void CWebPage::SetPageCode(string &pageCode)
{
	m_pageCode.clear();
	m_pageCode = pageCode;
}

inline string CWebPage::GetPageCode()
{
	return m_pageCode;
}

inline void CWebPage::SetPageRule(CRule *pageRule)
{
	m_pageRule = new CRule();
}

inline CRule* CWebPage::GetPageRule()
{
	return m_pageRule;
}

inline CArticle CWebPage::GetArticle()
{
    return m_articlesList[0];
}
