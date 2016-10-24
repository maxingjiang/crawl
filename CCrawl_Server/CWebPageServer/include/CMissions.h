#pragma once
#include "CMission.h"

class CMissions
{
private:
    vector<CMission*> m_missionList;

public:
    CMissions();
    virtual ~CMissions();

    unsigned int GetMissionListSize();
    int SetMissionList(vector<CMission*> missionList);
    int AddMission(CMission* mission);
    int AddMissionList(vector<CMission*> missionList);
    vector<CMission*> GetMissionList();
    CMission* GetMission(unsigned int &i);
    CMission* GetFirstMission() const;
    bool IsMissionListEmpty()const;
    int DeleteMission(int &missionId);
    int ClearMissionList();
};

inline unsigned int CMissions::GetMissionListSize()
{
    return m_missionList.size();
}

inline CMission* CMissions::GetMission(unsigned int &i)
{
    return m_missionList[i];
}

inline CMission* CMissions::GetFirstMission() const
{
    return m_missionList.front();
}

inline bool CMissions::IsMissionListEmpty()const
{
    return m_missionList.empty();
}
