#include "CRuleManager.h"
#include "readFile.h"

/*CRuleManager********************************/
CRuleManager::CRuleManager()
{
	m_pageCode = "";
	m_pageUrl = "";
    m_rule = new CRule();
    m_ruleMatchInfo = new CRuleMatchInfo();
}
CRuleManager::CRuleManager(string pageUrl, string pageCode)
{
	m_pageCode = pageCode;
	m_pageUrl = pageUrl;
    m_rule = new CRule(pageUrl);
    m_ruleMatchInfo = new CRuleMatchInfo();
}
CRuleManager::CRuleManager(string pageUrl)
{
	m_pageCode = "";
	m_pageUrl = pageUrl;
    m_rule = new CRule(pageUrl);
    m_ruleMatchInfo = new CRuleMatchInfo();
}

CRuleManager::~CRuleManager()
{
    delete m_rule;
    delete m_ruleMatchInfo;
}

string CRuleManager::GetJsonToStringFromLocal(const string &filename)
{
    string FileStrings;
    struct stat buf;
    FILE *fp;
    char *data;

    if(!(fp=fopen(filename.c_str(),"rb")))
        return "";
    stat(filename.c_str(),&buf);
    data=(char *)malloc(sizeof(char)*(buf.st_size+1));
    fread(data,sizeof(char),buf.st_size,fp);
    fclose(fp);
    data[buf.st_size]=0;
    FileStrings = data;
    free(data);

    return FileStrings;
}

string CRuleManager::GetJsonToStringFromDB()
{
    return "";
}

string CRuleManager::GetJsonToStringFromCloud()
{
    return "";
}
int CRuleManager::WriteJson(CRule *rule, string &ruleString)
{
    Json::Value Root;
    Json::Value RuleRoot;
    Json::Value parentNode;
    Json::Value childNode;
    Json::Value item;

    /*ruleName*/
    RuleRoot["ruleName"] = rule->m_ruleName;

    /*ruleDescription*/
    RuleRoot["ruleDescription"] = rule->m_ruleDescription;

    /*testUrl*/
    RuleRoot["testUrl"] = rule->m_testUrl;

    /*ruleType*/
    rule->m_ruleType.writeJson(RuleRoot);

    /*copyrightProtection*/
    rule->m_copyrightProtection.writeJson(RuleRoot);

    /*ruleMatchInfo*/
    rule->m_ruleMatchInfo.writeJson(RuleRoot);

    /*validArea*/
    rule->m_validArea.writeJson(RuleRoot);

    /*firstContentArea*/
    rule->m_firstContentArea.writeJson(RuleRoot);

    /*unitArea*/
    rule->m_unitArea.writeJson(RuleRoot);

    /*titleRule*/
    rule->m_titleRule.writeJson(RuleRoot);

    /*contentRule*/
    rule->m_contentRule.writeJson(RuleRoot);

    /*authorRule*/
    rule->m_authorRule.writeJson(RuleRoot);

    /*keywordRule*/
    rule->m_keywordRule.writeJson(RuleRoot);

    /*classifyRule*/
    rule->m_classifyRule.writeJson(RuleRoot);

    /*headPicRule*/
    rule->m_headPicRule.writeJson(RuleRoot);

    /*minPicRule*/
    rule->m_minPicRule.writeJson(RuleRoot);

    /*flipPageArea*/
    rule->m_flipPageArea.writeJson(RuleRoot);

    /*nextPageRule*/
    rule->m_nextPageRule.writeJson(RuleRoot);

    /*contentFlipPageArea*/
    rule->m_contentFlipPageArea.writeJson(RuleRoot);

    /*contentNextPageRule*/
    rule->m_contentNextPageRule.writeJson(RuleRoot);

    /*customRuleList*/
    for(unsigned int i = 0; i < rule->m_customRuleList.size(); i++)
    {
        CRuleItem unitRuleItem = rule->m_customRuleList[i];

        childNode["itemName"]     = unitRuleItem.m_childRuleName;
        childNode["helpInfo"]     = unitRuleItem.m_helpInfo;
        childNode["extractObject"]= unitRuleItem.m_extractObject;
        for(unsigned int i = 0; i < unitRuleItem.m_obtainCode.size(); i++)
        {
            CObtainCode unitObtainCode =unitRuleItem.m_obtainCode[i];
            unitObtainCode.writeJson(item);
            childNode["obtainCode"].append(item);
            item.clear();
        }
        parentNode.append(childNode);
        childNode.clear();
    }
    RuleRoot["customRuleList"]  = parentNode;

    Root["RuleRoot"] = RuleRoot;
    Root.toStyledString();
    ruleString = Root.toStyledString();
    return 0;
}

int CRuleManager::ReadJson(string &ruleString, CRule *rule)
{
    Json::Reader reader;
    Json::Value value;

    if (reader.parse(ruleString, value))
    {
        Json::Value RuleRoot = value["RuleRoot"];
        if(!RuleRoot.isNull())
        {
            Json::Value memberNode;

            /*ruleName*/
            rule->m_ruleName = RuleRoot["ruleName"].asString();

            /*ruleDescription*/
            rule->m_ruleDescription = RuleRoot["ruleDescription"].asString();

            /*testUrl*/
            rule->m_testUrl = RuleRoot["testUrl"].asString();

            /*ruleType*/
            memberNode = RuleRoot["ruleType"];
            if(!memberNode.isNull())
            {
                rule->m_ruleType.readJson(memberNode);
            }

            /*copyrightProtection*/
            memberNode = RuleRoot["copyrightProtection"];
            if(!memberNode.isNull())
            {
                rule->m_copyrightProtection.readJson(memberNode);
            }

            /*ruleMatchInfo*/
            memberNode = RuleRoot["ruleMatchInfo"];
            if(!memberNode.isNull())
            {
                rule->m_ruleMatchInfo.readJson(memberNode);
            }

            /*validArea*/
            memberNode = RuleRoot["validArea"];
            if(!memberNode.isNull())
            {
                rule->m_validArea.readJson(memberNode);
            }

            /*firstContentArea*/
            memberNode = RuleRoot["firstContentArea"];
            if(!memberNode.isNull())
            {
                rule->m_firstContentArea.readJson(memberNode);
            }

            /*unitArea*/
            memberNode = RuleRoot["unitArea"];
            if(!memberNode.isNull())
            {
                rule->m_unitArea.readJson(memberNode);
            }

            /*titleRule*/
            memberNode = RuleRoot["titleRule"];
            if(!memberNode.isNull())
            {
                rule->m_titleRule.readJson(memberNode);
            }

            /*contentRule*/
            memberNode = RuleRoot["contentRule"];
            if(!memberNode.isNull())
            {
                rule->m_contentRule.readJson(memberNode);
            }

            /*authorRule*/
            memberNode = RuleRoot["authorRule"];
            if(!memberNode.isNull())
            {
                rule->m_authorRule.readJson(memberNode);
            }

            /*keywordRule*/
            memberNode = RuleRoot["keywordRule"];
            if(!memberNode.isNull())
            {
                rule->m_keywordRule.readJson(memberNode);
            }

            /*classifyRule*/
            memberNode = RuleRoot["classifyRule"];
            if(!memberNode.isNull())
            {
                rule->m_classifyRule.readJson(memberNode);
            }

            /*headPicRule*/
            memberNode = RuleRoot["headPicRule"];
            if(!memberNode.isNull())
            {
                rule->m_headPicRule.readJson(memberNode);
            }

            /*minPicRule*/
            memberNode = RuleRoot["minPicRule"];
            if(!memberNode.isNull())
            {
                rule->m_minPicRule.readJson(memberNode);
            }

            /*flipPageArea*/
            memberNode = RuleRoot["flipPageArea"];
            if(!memberNode.isNull())
            {
                rule->m_flipPageArea.readJson(memberNode);
            }

            /*nextPageRule*/
            memberNode = RuleRoot["nextPageRule"];
            if(!memberNode.isNull())
            {
                rule->m_nextPageRule.readJson(memberNode);
            }

            /*contentFlipPageArea*/
            memberNode = RuleRoot["contentFlipPageArea"];
            if(!memberNode.isNull())
            {
                rule->m_contentFlipPageArea.readJson(memberNode);
            }

            /*contentNextPageRule*/
            memberNode = RuleRoot["contentNextPageRule"];
            if(!memberNode.isNull())
            {
                rule->m_contentNextPageRule.readJson(memberNode);
            }

            /*customRuleList*/
            memberNode = RuleRoot["customRuleList"];
            if(!memberNode.isNull())
            {
                const Json::Value parentArry = RuleRoot["customRuleList"];
                for (unsigned int i = 0; i < parentArry.size(); i++)
                {
                    Json::Value parentNode = parentArry[i];
                    CRuleItem unitRuleItem;
                    unitRuleItem.m_childRuleName = parentNode["itemName"].asString();
                    unitRuleItem.m_helpInfo = parentNode["helpInfo"].asString();
                    unitRuleItem.m_extractObject = parentNode["extractObject"].asInt();

                    const Json::Value childArry = parentNode["obtainCode"];
                    for (unsigned int i = 0; i < childArry.size(); i++)
                    {
                        CObtainCode unitObtainCode;

                        Json::Value childNode = childArry[i];
                        unitObtainCode.readJson(childNode);

                        unitRuleItem.m_obtainCode.push_back(unitObtainCode);
                    }
                    rule->m_customRuleList.push_back(unitRuleItem);
                }
            }
        }
    }
    return 0;
}

int CRuleManager::MatchRule(CWebPage* web, int Range, string fileName)
{
    string ruleString;
    web->m_pageRule = new CRule;

    switch(Range)
    {
        case 0:/*All Range*/
        {
            break;
        }
        case 1:/*Local File*/
        {
            //read file
            ruleString = GetJsonToStringFromLocal(fileName);

            //turn to rule class
            ReadJson(ruleString, web->m_pageRule);

            //turn rule to string
            ruleString = "";
            WriteJson(web->m_pageRule, ruleString);

            //cout << ruleString << endl;

            //string cmd = string("echo \'") + ruleString + "\' >> "+"./b.txt";
            //system(cmd.c_str());

            break;
        }
        case 2:/*Rule DateBase*/
        {
            break;
        }
        case 3:/*Cloud*/
        {
            break;
        }
    }
    return 0;
}

bool CRuleManager::UpdaeRule()
{
	//Updae...
	return false;
}
bool CRuleManager::AddRule()
{
	//Add...
	return false;
}
CRule* CRuleManager::SerchRule()
{
	CRule* rule = new CRule;
	//Search...
	return rule;
}
bool CRuleManager::DeleteRule()
{
	//Delete
	return false;
}
/*********************************************/
