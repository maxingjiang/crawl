#pragma once
#include "CBaseItem.h"

//规则版权信息
class CCopyrightProtection
{
public:
    int m_protectFlag;		//保护标志
    string m_ruleAuthor;		//规则作者
	string m_copyrightId;	//版权编号
	string m_contectInfo;	//联系信息
	int m_trialCount;		//试用次数

public:
	CCopyrightProtection();
	virtual ~CCopyrightProtection();

	void SetProtectFlag(bool protectFlag);
	bool GetProtectFlag();

	void SetRuleAuthor(string ruleAuthor);
	string GetRuleAuthor();

	void SetCopyrightId(string copyrightId);
	string GetCopyrightId();

	void SetContectInfo(string contectInfo);
	string GetContectInfo();

	void SetTrialCount(int trialCount);
	int GetTrialCount();

    int readJson(Json::Value &root);
    int writeJson(Json::Value &root);
};

inline CCopyrightProtection::CCopyrightProtection()
{
	m_protectFlag = false;
    m_ruleAuthor = "";
	m_copyrightId = "";
	m_contectInfo = "";
	m_trialCount = 0;
}
inline CCopyrightProtection::~CCopyrightProtection()
{

}

inline void CCopyrightProtection::SetProtectFlag(bool protectFlag)
{
	m_protectFlag = protectFlag;
}
inline bool CCopyrightProtection::GetProtectFlag()
{
	return m_protectFlag;
}

inline void CCopyrightProtection::SetRuleAuthor(string ruleAuthor)
{
    m_ruleAuthor = ruleAuthor;
}
inline string CCopyrightProtection::GetRuleAuthor()
{
    return m_ruleAuthor;
}

inline void CCopyrightProtection::SetCopyrightId(string copyrightId)
{
	m_copyrightId = copyrightId;
}
inline string CCopyrightProtection::GetCopyrightId()
{
	return m_copyrightId;
}

inline void CCopyrightProtection::SetContectInfo(string contectInfo)
{
	m_contectInfo = contectInfo;
}
inline string CCopyrightProtection::GetContectInfo()
{
	return m_contectInfo;
}

inline void CCopyrightProtection::SetTrialCount(int trialCount)
{
	m_trialCount = trialCount;
}
inline int CCopyrightProtection::GetTrialCount()
{
	return m_trialCount;
}
