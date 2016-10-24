#ifndef CTask_H
#define CTask_H
#include "CJobMgr.h"

#define TASK_STATUS_INVALID     -1
#define TASK_STATUS_READY       0
#define TASK_STATUS_RUNNING     1
#define TASK_STATUS_WAITING     2
#define TASK_STATUS_COMPLETE    3

class CTask
{
private:
    static int taskId;
    int m_taskId;
    int m_taskStatus;

    string m_url;

    CJobMgr m_jobMgr;

public:
    CTask();
    virtual ~CTask();

    void SetTaskId(int &taskId);
    int GetTaskId();

    void SetTaskStatus(int &taskStatus);
    int GetTaskStatus();

    void SetUrl(string &url);
    string GetUrl();

    int InitTask(string &url);
    int CreateJob(int jobStatus);
    int DeleteJob(CJob* job);
    CJob* GetFirstJob();
};

inline void CTask::SetTaskId(int &taskId)
{
    m_taskId = taskId;
}

inline int CTask::GetTaskId()
{
    return m_taskId;
}

inline void CTask::SetTaskStatus(int &taskStatus)
{
    m_taskStatus = taskStatus;
}

inline int CTask::GetTaskStatus()
{
    return m_taskStatus;
}

inline void CTask::SetUrl(string &url)
{
    m_url = url;
}

inline string CTask::GetUrl()
{
    return m_url;
}



#endif // CTask_H
