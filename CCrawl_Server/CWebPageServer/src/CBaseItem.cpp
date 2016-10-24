#include "CBaseItem.h"

//静态成员初始化
int CBaseItem::itemIdCount = 0;

/*CBaseItem***********************************/
CBaseItem::CBaseItem()
{
    //m_childRuleId = ++itemIdCount;
    m_childRuleName = "";
	m_helpInfo = "";
    m_childRule = "";
	m_extractObject = 4;//默认为固定值
}
CBaseItem::CBaseItem(string &childRule)
{
    //m_childRuleId = itemIdCount++;
    m_childRuleName = "";
	m_helpInfo = "";
    m_childRule = childRule;
	m_extractObject = 4;//默认为固定值
}
CBaseItem::~CBaseItem()
{

}

CBaseItem::CBaseItem(int &childRuleId)
{
    m_childRuleId = childRuleId;
    m_childRuleName = "";
	m_helpInfo = "";
    m_childRule = "";
	m_extractObject = 4;//默认为固定值
}
CBaseItem::CBaseItem(int &childRuleId, string &childRuleName)
{
    m_childRuleId = childRuleId;
    m_childRuleName = childRuleName;
	m_helpInfo = "";
    m_childRule = "";
	m_extractObject = 4;//默认为固定值
}
CBaseItem::CBaseItem(int &childRuleId, string &childRuleName, string &helpInfo)
{
    m_childRuleId = childRuleId;
    m_childRuleName = childRuleName;
	m_helpInfo = helpInfo;
    m_childRule = "";
	m_extractObject = 4;//默认为固定值
}
CBaseItem::CBaseItem(int &childRuleId, string &childRuleName, string &helpInfo, string &childRule)
{
    m_childRuleId = childRuleId;
    m_childRuleName = childRuleName;
	m_helpInfo = helpInfo;
    m_childRule = childRule;
	m_extractObject = 4;//默认为固定值
}
int CBaseItem::readJson(Json::Value &root)
{
    m_childRule = root.asString();
    return 0;
}
int CBaseItem::writeJson(Json::Value &root)
{
    root[m_childRuleName] = m_childRule;
    return 0;
}

/*********************************************/
