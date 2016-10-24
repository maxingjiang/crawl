#include "CCopyrightProtection.h"

int CCopyrightProtection::readJson(Json::Value &root)
{
    m_protectFlag = root["protectFlag"].asInt();
    m_ruleAuthor = root["ruleAuthor"].asString();
    m_copyrightId = root["copyrightId"].asString();
    m_contectInfo = root["contectInfo"].asString();
    m_trialCount = root["trialCount"].asInt();
    return 0;
}

int CCopyrightProtection::writeJson(Json::Value &root)
{
    Json::Value item;
    item["protectFlag"]  = m_protectFlag;
    item["ruleAuthor"]   = m_ruleAuthor;
    item["copyrightId"]  = m_copyrightId;
    item["contectInfo"]  = m_contectInfo;
    item["trialCount"]   = m_trialCount;
    root["copyrightProtection"]  = item;
    item.clear();
    return 0;
}
