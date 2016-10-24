#pragma once
#include "include.h"
#include "CMissionMap.h"
#include "CTaskManager.h"

#define MISSION_STATUS_INVALID     -1
#define MISSION_STATUS_READY        0
#define MISSION_STATUS_RUNNING      1
#define MISSION_STATUS_WAITING      2
#define MISSION_STATUS_COMPLETE     3

class CMission
{
private:
    static int missionId;

    int m_missionId;
    int m_missionStatus;
    string m_mainUrl;

    CCollector* m_collector;

    CTaskManager m_taskMgr;

    CMissionMap m_missionMap;

public:
    CMission();
    virtual ~CMission();

    int initMission(string &mainUrl, CCollector* collector);

    void SetMissionId(int &missionId);
    int GetMissionId();

    void SetMissionStatus(int &missionStatus);
    int GetMissionStatus();

    void SetMainUrl(string &mainUrl);
    string GetMainUrl();

    void SetCollector(CCollector* collector);
    CCollector* GetCollector()const;

    int CreateTask(string &mainUrl);
    int DeleteTask(CTask* task);
    CTask* GetTask();

};

inline void CMission::SetMissionId(int &missionId)
{
    m_missionId = missionId;
}

inline int CMission::GetMissionId()
{
    return m_missionId;
}

inline void CMission::SetMissionStatus(int &missionStatus)
{
    m_missionStatus = missionStatus;
}

inline int CMission::GetMissionStatus()
{
    return m_missionStatus;
}

inline void CMission::SetMainUrl(string &mainUrl)
{
    m_mainUrl = mainUrl;
}

inline string CMission::GetMainUrl()
{
    return m_mainUrl;
}

inline void CMission::SetCollector(CCollector* collector)
{
    m_collector = collector;
}

inline CCollector* CMission::GetCollector()const
{
    return m_collector;
}
