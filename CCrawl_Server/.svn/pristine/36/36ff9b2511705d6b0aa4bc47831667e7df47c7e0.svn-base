#pragma once
#include "CBaseItem.h"
#include "CObtainCode.h"
//采集规则
class CRuleItem
{
public:
    string m_childRuleName;
    string m_helpInfo;
    string m_childRule;
    int m_extractObject;/*提取对象 0-提取正文 1-提取连接地址 2-提取图片地址
                        3-提取html代码 4-固定值 5-关键词之后 6-随机行 7-时间
                        8-提取ubb代码 9-提取map 10-验证码 11-文字识别*/
    vector<CObtainCode> m_obtainCode;
    string m_obtainContent;//获取的内容

public:
	CRuleItem();
    CRuleItem(string itemName);
    CRuleItem(string itemName, string helpInfo);
    CRuleItem(string itemName, string helpInfo, int extractObject);

	virtual ~CRuleItem();

	void AddObainCode(CObtainCode* obtainCode);
	void RemoveObainCode(CObtainCode* obtainCode);

    int readJson(Json::Value &root);
    int writeJson(Json::Value &root);
};
