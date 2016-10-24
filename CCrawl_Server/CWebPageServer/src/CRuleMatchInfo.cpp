#include "CRuleMatchInfo.h"


/*CRuleMatchInfo******************************/
CRuleMatchInfo::CRuleMatchInfo()
{
    m_matchFlag = 0;
    m_urlInclude = "";
    m_urlNotInclude = "";
    m_codeInclude = "";
    m_codeNotInclude = "";
}
CRuleMatchInfo::~CRuleMatchInfo()
{

}

void CRuleMatchInfo::SetMatchInfo()
{

}

int CRuleMatchInfo::readJson(Json::Value &root)
{
    m_matchFlag = root["matchFlag"].asInt();
    m_urlInclude = root["urlInclude"].asString();
    m_urlNotInclude = root["urlNotInclude"].asString();
    m_codeInclude = root["codeInclude"].asString();
    m_codeNotInclude = root["codeNotInclude"].asString();
    return 0;
}

int CRuleMatchInfo::writeJson(Json::Value &root)
{
    Json::Value item;
    item["matchFlag"]      = m_matchFlag;
    item["urlInclude"]     = m_urlInclude;
    item["urlNotInclude"]  = m_urlNotInclude;
    item["codeInclude"]    = m_codeInclude;
    item["codeNotInclude"] = m_codeNotInclude;
    root["ruleMatchInfo"]  = item;
    item.clear();
    return 0;
}
/*********************************************/
