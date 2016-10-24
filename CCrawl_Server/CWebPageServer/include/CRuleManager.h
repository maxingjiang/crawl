#pragma once
#include "CWebPage.h"

//规则管理器
class CRuleManager
{
private:
	string m_pageCode;
	string m_pageUrl;
    CRule* m_rule;
    CRuleMatchInfo* m_ruleMatchInfo;

public:
	CRuleManager();
	CRuleManager(string pageUrl);
	CRuleManager(string pageUrl, string pageCode);
	
	virtual ~CRuleManager();

	void SetPageCode(string &pageCode);
	string GetPageCode();

	void SetPageUrl(string &pageUrl);
	string GetPageUrl();

    int ReadJson(string &ruleString, CRule *rule);
    int WriteJson(CRule *rule, string &ruleString);
    int MatchRule(CWebPage* web, int Range, string fileName = "");
	CRule* GetRule();

private:
    string GetJsonToStringFromLocal(const string &filename);
    string GetJsonToStringFromDB();
    string GetJsonToStringFromCloud();

public:
	/*规则库管理*/
	bool UpdaeRule();
	bool AddRule();
	CRule* SerchRule();
	bool DeleteRule();
};

inline void CRuleManager::SetPageCode(string &pageCode)
{
	m_pageCode = pageCode;
}
inline string CRuleManager::GetPageCode()
{
	return m_pageCode;
}

inline void CRuleManager::SetPageUrl(string &pageUrl)
{
	m_pageUrl = pageUrl;
}
inline string CRuleManager::GetPageUrl()
{
	return m_pageUrl;
}
inline CRule* CRuleManager::GetRule()
{
    //match rule from rule database

    //or match rule form rule cloud

    //or get rule form local text

    return m_rule;
}
