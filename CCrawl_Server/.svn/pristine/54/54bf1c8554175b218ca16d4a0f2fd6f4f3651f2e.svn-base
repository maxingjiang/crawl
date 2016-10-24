#include "CRuleType.h"

int CRuleType::readJson(Json::Value &root)
{
    m_pageType = root["pageType"].asInt();
    m_pageCodeSource = root["pageCodeSource"].asInt();
    return 0;
}

int CRuleType::writeJson(Json::Value &root)
{
    Json::Value item;
    item["pageType"]      = m_pageType;
    item["pageCodeSource"]= m_pageCodeSource;

    root["ruleType"]  = item;
    item.clear();

    return 0;
}
