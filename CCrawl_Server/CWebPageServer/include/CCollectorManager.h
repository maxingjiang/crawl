#pragma once
#include "CThreadManager.h"

class CCollectorManager
{
public:
	CCollectorManager();
	virtual ~CCollectorManager();

    int CreateCollectorMission(string &url);
    int LoadCollectorMission();
    int StopAllCollectorMission(int& stopModel);

private:
    CCollector* CreateCollector(string &url);
    int InitCollectorMgr(int threadPoolCount);
    CCollector* GetCollector(string url)const;

private: 
    CMissionMgr m_missionMgr;
    CThreadManager m_threadMgr;

	vector<CCollector*> m_collectorList;
    CCrawlManager m_crawlMgr;
    CProxy m_proxy;
    CRequestHeaders m_requestHeaders;

    CRuleManager m_ruleManager;		//规则管理器
};
