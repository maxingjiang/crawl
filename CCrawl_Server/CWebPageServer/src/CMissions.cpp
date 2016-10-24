#include "CMissions.h"

CMissions::CMissions()
{
    m_missionList.clear();
}

CMissions::~CMissions()
{
    m_missionList.clear();
}

int CMissions::SetMissionList(vector<CMission*> missionList)
{
    try
    {
        for (vector<CMission*>::size_type i = 0;i < missionList.size();i++)
        {
            m_missionList.push_back(missionList[i]);
        }
    }
    catch (int id)
    {
        cout << "Exception:" << id << endl;
        return 1;
    }
    catch (out_of_range &e)
    {
        cout << "an exception of out_of_range:" << e.what() << endl;
        return 1;
    }
    catch (bad_alloc &e)
    {
        cout << "an exception of an unexpected type:" << e.what() << endl;
        return 1;
    }
    return 0;
}
int CMissions::AddMission(CMission* mission)
{
    try
    {
        m_missionList.push_back(mission);
    }
    catch (int id)
    {
        cout << "Exception:" << id << endl;
        return 1;
    }
    catch (out_of_range &e)
    {
        cout << "an exception of out_of_range:" << e.what() << endl;
        return 1;
    }
    catch (bad_alloc &e)
    {
        cout << "an exception of an unexpected type:" << e.what() << endl;
        return 1;
    }
    return 0;
}

int CMissions::AddMissionList(vector<CMission*> missionList)
{
    for(unsigned int i = 0; i < missionList.size(); i++)
    {
        m_missionList.push_back(missionList[i]);
    }
    return 0;
}
vector<CMission*> CMissions::GetMissionList()
{
    return m_missionList;
}

int CMissions::ClearMissionList()
{
    try
    {
        for (vector<CMission*>::size_type i = 0;i < m_missionList.size();i++)
        {
            CMission* tempMission = m_missionList[i];
            delete tempMission;
        }
        m_missionList.clear();
    }
    catch (int id)
    {
        cout << "Exception:" << id << endl;
        return 1;
    }
    catch (out_of_range &e)
    {
        cout << "an exception of out_of_range:" << e.what() << endl;
        return 1;
    }
    catch (bad_alloc &e)
    {
        cout << "an exception of an unexpected type:" << e.what() << endl;
        return 1;
    }
    return 0;
}

int CMissions::DeleteMission(int &missionId)
{
    try
    {
        for (vector<CMission*>::size_type i = 0;i < m_missionList.size();i++)
        {
            CMission* tempMission = m_missionList[i];
            if (tempMission->GetMissionId() == missionId)
            {
                delete tempMission;
                m_missionList.erase(m_missionList.begin() + i);
            }
        }
    }
    catch (int ExceptionId)
    {
        cout << "Exception:" << ExceptionId << endl;
        return 1;
    }
    catch (out_of_range &e)
    {
        cout << "an exception of out_of_range:" << e.what() << endl;
        return 1;
    }
    catch (bad_alloc &e)
    {
        cout << "an exception of an unexpected type:" << e.what() << endl;
        return 1;
    }
    return 0;
}
