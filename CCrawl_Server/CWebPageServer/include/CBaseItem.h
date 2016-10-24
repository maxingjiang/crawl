#pragma once
#include "include.h"
#include "json/json.h"

//规则基类
class CBaseItem
{
public:
	static int itemIdCount;
    int m_childRuleId;
    string m_childRuleName;
	string m_helpInfo;
    string m_childRule;
	int m_extractObject;/*提取对象 0-提取正文 1-提取连接地址 2-提取图片地址
						3-提取html代码 4-固定值 5-关键词之后 6-随机行 7-时间
						8-提取ubb代码 9-提取map 10-验证码 11-文字识别*/

public:
	CBaseItem();
	virtual ~CBaseItem();

    CBaseItem(int &childRuleId);
    CBaseItem(string &childRule);
    CBaseItem(int &childRuleId, string &childRuleName);
    CBaseItem(int &childRuleId, string &childRuleName, string &helpInfo);
    CBaseItem(int &childRuleId, string &childRuleName, string &helpInfo, string &childRule);

    void SetChildRuleId(int &childRuleId);
    int GetChildRuleId();

    void SetChildRuleName(string &childRuleName);
    string GetChildRuleName();

    void SetHelpInfo(string &helpInfo);
	string GetHelpInfo();

    void SetChildRule(string &childRule);
    string GetChildRule();

    void SetExtractObject(int &extractObject);
	int GetExtractObject();

    virtual int readJson(Json::Value &root);
    virtual int writeJson(Json::Value &root);
};

inline void CBaseItem::SetChildRuleId(int &childRuleId)
{
    m_childRuleId = childRuleId;
}

inline int CBaseItem::GetChildRuleId()
{
    return m_childRuleId;
}

inline void CBaseItem::SetChildRuleName(string &childRuleName)
{
    m_childRuleName = childRuleName;
}

inline string CBaseItem::GetChildRuleName()
{
    return m_childRuleName;
}

inline void CBaseItem::SetHelpInfo(string &helpInfo)
{
	m_helpInfo = helpInfo;
}

inline string CBaseItem::GetHelpInfo()
{
	return m_helpInfo;
}

inline void CBaseItem::SetChildRule(string &childRule)
{
    m_childRule = childRule;
}

inline string CBaseItem::GetChildRule()
{
    return m_childRule;
}

inline void CBaseItem::SetExtractObject(int &extractObject)
{
	m_extractObject = extractObject;
}

inline int CBaseItem::GetExtractObject()
{
	return m_extractObject;
}
