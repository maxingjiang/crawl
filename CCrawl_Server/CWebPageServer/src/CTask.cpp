#include "CTask.h"
#include "CCollector.h"

int CTask::taskId = -1;

CTask::CTask()
{
    m_taskId = ++taskId;
    m_taskStatus = TASK_STATUS_INVALID;
    m_url = "";
}

CTask::~CTask()
{

}

int CTask::InitTask(string &url)
{
    m_url = url;
    CreateJob(JOB_STATUS_READY);
    m_taskStatus = TASK_STATUS_READY;
    return 0;
}

int CTask::CreateJob(int jobStatus)
{
    m_jobMgr.CreateJob(jobStatus);
    return 0;
}

int CTask::DeleteJob(CJob* job)
{
    int jobId = job->GetJobId();
    m_jobMgr.DeleteJob(jobId);
    return 0;
}

CJob* CTask::GetFirstJob()
{
    CJob* job = NULL;
    job = m_jobMgr.GetFirstJob();
    return job;
}
