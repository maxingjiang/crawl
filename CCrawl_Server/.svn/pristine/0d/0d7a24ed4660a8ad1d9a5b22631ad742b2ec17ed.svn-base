#pragma once
#include "CBaseItem.h"
//规则类型
class CRuleType
{
public:
	int m_pageType;			//0-源代码  1-浏览器代码
	int m_pageCodeSource;	/*0-列表页  1-正文页  2-下载		*/
							/*3-跳转    4-小说章节页  5-帐号	*/
							/*6-网盘    7-翻译	8-打码		*/
public:
	CRuleType();
	virtual ~CRuleType();

	void SetPageType(int pageType);
	int GetPageType();

	void SetPageCodeSource(int pageCodeSource);
	int GetPageCodeSource();

    int readJson(Json::Value &root);
    int writeJson(Json::Value &root);
};

inline CRuleType::CRuleType()
{
	m_pageType = SOURCECODE;
	m_pageCodeSource = PAGE_TYPE_LIST;
}

inline CRuleType::~CRuleType()
{

}

inline void CRuleType::SetPageType(int pageType)
{
	m_pageType = pageType;
}

inline int CRuleType::GetPageType()
{
	return m_pageType;
}

inline void CRuleType::SetPageCodeSource(int pageCodeSource)
{
	m_pageCodeSource = pageCodeSource;
}

inline int CRuleType::GetPageCodeSource()
{
	return m_pageCodeSource;
}
