#include "CRuleItem.h"

/*CRuleItem***********************************/
CRuleItem::CRuleItem()
{
    m_childRuleName = "";
    m_helpInfo = "";
    m_extractObject = EXTRACT_OBJECT_CONTENT;
}

CRuleItem::CRuleItem(string itemName)
{
    m_childRuleName = itemName;
    m_helpInfo = "";
    m_extractObject = EXTRACT_OBJECT_CONTENT;
}
CRuleItem::CRuleItem(string itemName, string helpInfo)
{
	m_childRuleName = itemName;
	m_helpInfo = helpInfo;
    m_extractObject = EXTRACT_OBJECT_CONTENT;
}

CRuleItem::CRuleItem(string itemName, string helpInfo, int extractObject)
{
	m_childRuleName = itemName;
	m_helpInfo = helpInfo;
    m_extractObject = extractObject;
}
CRuleItem::~CRuleItem()
{

}

int CRuleItem::readJson(Json::Value &root)
{
    Json::Value Node = root["obtainCode"];

    for (unsigned int i = 0; i < Node.size(); i++)
    {
        CObtainCode unitObtainCode;
        unitObtainCode.readJson(Node[i]);
        m_obtainCode.push_back(unitObtainCode);
    }
    return 0;
}
int CRuleItem::writeJson(Json::Value &root)
{
    Json::Value item;
    Json::Value childNode;
    Json::Value parentNode;
    for(unsigned int i = 0; i < m_obtainCode.size(); i++)
    {
        CObtainCode unitObtainCode = m_obtainCode[i];
        unitObtainCode.writeJson(item);
        childNode.append(item);
        item.clear();
    }
    parentNode["obtainCode"] = childNode;
    root[m_childRuleName]  = parentNode;
    childNode.clear();
    return 0;
}

void CRuleItem::AddObainCode(CObtainCode* obtainCode)
{

}
void CRuleItem::RemoveObainCode(CObtainCode* obtainCode)
{

}
/*********************************************/
