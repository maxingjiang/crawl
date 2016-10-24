#pragma once
#include "CJob.h"

class CJobMgr
{
private:
    vector<CJob*> m_jobList;

public:
    CJobMgr();
    virtual ~CJobMgr();

    unsigned int GetJobListSize();
    int SetJobList(vector<CJob*> job);
    int PushBackJob(CJob* job);
    int AddJobList(vector<CJob*> job);
    vector<CJob*> GetJobList();
    CJob* GetJob(unsigned int &i);
    CJob* GetFirstJob() const;
    bool IsJobListEmpty()const;
    int DeleteJob(int &jobId);
    int ClearJobList();

    int CreateJob(int &jobStatus);
};

inline unsigned int CJobMgr::GetJobListSize()
{
    return m_jobList.size();
}

inline CJob* CJobMgr::GetJob(unsigned int &i)
{
    return m_jobList[i];
}

inline CJob* CJobMgr::GetFirstJob() const
{
    return m_jobList.front();
}

inline bool CJobMgr::IsJobListEmpty()const
{
    return m_jobList.empty();
}
