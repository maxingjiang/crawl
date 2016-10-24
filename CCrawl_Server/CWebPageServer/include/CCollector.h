#pragma once

#include "CRuleManager.h"
#include "CCrawlManager.h"
#include "CTaskManager.h"
#include "CMissionMgr.h"
#include "CWebPageMgr.h"
#include "CMissions.h"
#include "CTasks.h"

#define COLLECTOR_STATUS_INVALID    -1
#define COLLECTOR_STATUS_WORKDOWN   1
#define COLLECTOR_STATUS_INIT       0

#define COLLECTOR_ERROR_NOMISSION   1
#define COLLECTOR_ERROR_CRAWL       2
#define COLLECTOR_ERROR_WEBPAGE     3
#define COLLECTOR_ERROR_ARTICL      4
#define COLLECTOR_ERROR_RULE        5

#define COLLECTOR_MISSION_ERROR_NOTASK          10
#define COLLECTOR_MISSION_ERROR_WRONG_STATUS    11

#define COLLECTOR_TASK_ERROR_NOJOB  20
#define COLLECTOR_TASK_ERROR_WRONG_STATUS 21

#define COLLECTOR_JOB_ERROR_WRONG_STATUS 31


//采集器类
class CCollector
{
private:
    int m_workStatus;
	int m_workModel;					//
	string m_mainUrl;					//主链接

    vector<string> m_unexecuteUrl;
    vector<string> m_executeUrl;

    CCrawl* m_crawl;					//爬虫
    CRuleManager* m_ruleManager;		//规则管理器
    CRuleInterpreter m_ruleInterpreter;
    CMissionMgr* m_missionMgr;
    CWebPageMgr m_webPageMgr;

    CMissions m_missions;
    CTasks m_tasks;

    CMission* m_currentMission;
    CWebPage* m_currentWebPage;

public:
	CCollector();
	virtual ~CCollector();

    int InitCollector(CCrawl* crawl, CMissionMgr* missionMgr, CRuleManager* ruleMgr, CMission* mission);

    void SetWorkStatus(int workStatus);
    int GetWorkStatus();

    void SetWorkModel(int workModel);
    int GetWorkModel()const;

    void SetMainUrl(string &mainUrl);
	string GetMainUrl()const;

    void SetRuleManager(CRuleManager* ruleManager);
    CRuleManager* GetRuleManager();

    void SetCrawl(CCrawl* crawl);
    CCrawl* GetCrawl();

    void SetMissionMgr(CMissionMgr* missionMgr);
    CMissionMgr* GetMissionMgr();

    unsigned int GetUnexecuteUrlSize();
    bool SetUnexecuteUrl(vector<string> &unexecuteUrl);
    bool AddUnexecuteUrl(string &unexecuteUrl);
    void AddUnexecuteUrl(vector<string> &unexecuteUrl);
    vector<string> GetUnexecuteUrl();
    string GetUnexecuteUrl(unsigned int &i);
    string GetUnexecuteUrlBegin() const;
    bool IsUnexecuteUrlEmpty()const;
    bool DeleteUnexecuteUrl(string &childUrl);
    bool ClearUnexecuteUrl();

    unsigned int GetExecuteUrlSize();
    bool SetExecuteUrl(vector<string> &unexecuteUrl);
    bool AddExecuteUrl(string &unexecuteUrl);
    void AddExecuteUrl(vector<string> &unexecuteUrl);
    vector<string> GetExecuteUrl();
    string GetExecuteUrl(unsigned int &i);
    string GetExecuteUrlBegin() const;
    bool IsExecuteUrlEmpty()const;
    bool DeleteExecuteUrl(string &childUrl);
    bool ClearExecuteUrl();

    int GetChildUrlFromWebPage(CWebPage* webpage);

    int Run();

    int AddTask(CTask* task);

private:
    int AddJob(int jobStatus);
    int CreateMission(string &mainUrl);
    int CreateTask(string &url);

    int InitWebPage();
    int CrawlWebPage();
    int MatchRule();
    int ParseWebPage();
    int ExtractWebPage();
    int SaveWebPage();
    int PrintWebPage();
    int DeleteTask(CTask* task);

private:
    int CrawlUrl(CCrawl* crawl, CWebPage* webPage);
};

inline void CCollector::SetMainUrl(string &mainUrl)
{
	m_mainUrl = mainUrl;
}

inline string CCollector::GetMainUrl()const
{
	return m_mainUrl;
}

inline void CCollector::SetWorkStatus(int workStatus)
{
    m_workStatus = workStatus;
}

inline int CCollector::GetWorkStatus()
{
    return m_workStatus;
}

inline void CCollector::SetWorkModel(int workModel)
{
    m_workModel = workModel;
}

inline int CCollector::GetWorkModel()const
{
    return m_workModel;
}

inline unsigned int CCollector::GetUnexecuteUrlSize()
{
    return m_unexecuteUrl.size();
}

inline string CCollector::GetUnexecuteUrl(unsigned int &i)
{
    return m_unexecuteUrl[i];
}

inline string CCollector::GetUnexecuteUrlBegin() const
{
    return m_unexecuteUrl.front();
}

inline bool CCollector::IsUnexecuteUrlEmpty()const
{
    return m_unexecuteUrl.empty();
}

inline unsigned int CCollector::GetExecuteUrlSize()
{
    return m_executeUrl.size();
}

inline string CCollector::GetExecuteUrl(unsigned int &i)
{
    return m_executeUrl[i];
}

inline string CCollector::GetExecuteUrlBegin() const
{
    return m_executeUrl.front();
}

inline bool CCollector::IsExecuteUrlEmpty()const
{
    return m_executeUrl.empty();
}

inline void CCollector::SetCrawl(CCrawl* crawl)
{
    m_crawl = crawl;
}

inline CCrawl* CCollector::GetCrawl()
{
    return m_crawl;
}

inline void CCollector::SetRuleManager(CRuleManager* ruleManager)
{
    m_ruleManager = ruleManager;
}

inline CRuleManager* CCollector::GetRuleManager()
{
    return m_ruleManager;
}
inline void CCollector::SetMissionMgr(CMissionMgr* missionMgr)
{
    m_missionMgr = missionMgr;
}

inline CMissionMgr* CCollector::GetMissionMgr()
{
    return m_missionMgr;
}

