#pragma once
#include "CBaseItem.h"

//规则匹配信息
class CRuleMatchInfo
{
public:
    int m_matchFlag;
    string m_urlInclude;
    string m_urlNotInclude;
    string m_codeInclude;
    string m_codeNotInclude;

	CRuleMatchInfo();
	virtual ~CRuleMatchInfo();

	void SetMatchInfo();

    int readJson(Json::Value &root);
    int writeJson(Json::Value &root);
};
