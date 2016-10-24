#pragma once
#include "CMission.h"

class CMissionMgr
{
private:
    vector<CMission*> m_missionList;

public:
    CMissionMgr();
    virtual ~CMissionMgr();

    unsigned int GetMissionListSize();
    int SetMissionList(vector<CMission*> missionList);
    int AddMission(CMission* mission);
    int AddMissionList(vector<CMission*> missionList);
    vector<CMission*> GetMissionList();
    CMission* GetMission(unsigned int i);
    CMission* GetFirstMission() const;
    bool IsMissionListEmpty()const;
    int DeleteMission(int missionId);
    int ClearMissionList();

    int CreateMission(string &mainUrl, CMission** mission, CCollector* collector);
};

inline unsigned int CMissionMgr::GetMissionListSize()
{
    return m_missionList.size();
}

inline CMission* CMissionMgr::GetMission(unsigned int i)
{
    return m_missionList[i];
}

inline CMission* CMissionMgr::GetFirstMission() const
{
    return m_missionList.front();
}

inline bool CMissionMgr::IsMissionListEmpty()const
{
    return m_missionList.empty();
}
