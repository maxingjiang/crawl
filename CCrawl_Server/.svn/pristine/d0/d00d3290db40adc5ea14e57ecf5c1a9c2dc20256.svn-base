#pragma once
#include "CRuleItem.h"
#include "CRuleType.h"
#include "CCopyrightProtection.h"
#include "CRuleMatchInfo.h"

//规则类
class CRule
{
public:
    string m_ruleName;
    string m_ruleDescription;
    string m_testUrl;

    CRuleType m_ruleType;

    CCopyrightProtection m_copyrightProtection;

    CRuleMatchInfo m_ruleMatchInfo;

	/*预定义项目规则*/
    CRuleItem m_validArea = CRuleItem("validArea","");
    CRuleItem m_firstContentArea = CRuleItem("firstContentArea","");
    CRuleItem m_unitArea = CRuleItem("unitArea","");
    CRuleItem m_titleRule = CRuleItem("titleRule","");
    CRuleItem m_contentRule = CRuleItem("contentRule","");
    CRuleItem m_authorRule = CRuleItem("authorRule","");
    CRuleItem m_keywordRule = CRuleItem("keywordRule","");
    CRuleItem m_classifyRule = CRuleItem("classifyRule","");
    CRuleItem m_headPicRule = CRuleItem("headPicRule","");
    CRuleItem m_minPicRule = CRuleItem("minPicRule","");

	/*自定义项目规则*/
	vector <CRuleItem> m_customRuleList;

	/*翻页规则*/
    CRuleItem m_flipPageArea = CRuleItem("flipPageArea","");
    CRuleItem m_nextPageRule = CRuleItem("nextPageRule","");
    CRuleItem m_contentFlipPageArea = CRuleItem("contentFlipPageArea","");
    CRuleItem m_contentNextPageRule = CRuleItem("contentNextPageRule","");

public:
	CRule();
	CRule(string pageUrl);
	virtual ~CRule();

	bool AddCustomItem(CRuleItem* ruleItem);
};


