#include "CJob.h"

int CJob::jobId = -1;

CJob::CJob()
{
    m_jobId = ++jobId;
    m_jobStatus = JOB_STATUS_INVALID;
}

CJob::~CJob()
{

}

int CJob::InitJob(int jobStatus)
{
    m_jobStatus = jobStatus;
    return 0;
}


