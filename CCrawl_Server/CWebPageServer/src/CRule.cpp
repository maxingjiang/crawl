#include "CRule.h"






/*CRule***************************************/
CRule::CRule()
{
    m_ruleName = "";

	m_customRuleList.clear();
}
CRule::CRule(string pageUrl)
{
    m_testUrl = pageUrl;
	m_customRuleList.clear();
}
CRule::~CRule()
{

}

bool CRule::AddCustomItem(CRuleItem* ruleItem)
{
	return false;
}
/*********************************************/


