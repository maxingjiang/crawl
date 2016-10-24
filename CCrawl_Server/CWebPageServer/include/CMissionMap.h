#pragma once
#include "include.h"
class CMission;

class CMissionMap
{
private:
    int m_nodeCount;

    CMission* m_parentsMission;
    vector<CMission*> m_childMissionList;

public:
    CMissionMap();
    virtual ~CMissionMap();

    void SetParentsMission(CMission* parentsMission);
    CMission* GetParentsMission();

    int AddChildMission(CMission* childMission);
    bool IsTaskExist(string &url);
};

inline void CMissionMap::SetParentsMission(CMission* parentsMission)
{
    m_parentsMission = parentsMission;
}

inline CMission* CMissionMap::GetParentsMission()
{
    return m_parentsMission;
}
