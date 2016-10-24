#ifndef CJob_H
#define CJob_H
#include<include.h>

#define JOB_STATUS_INVALID     -1
#define JOB_STATUS_READY       0
#define JOB_STATUS_CRAWL       1
#define JOB_STATUS_MATCH_RULE  2
#define JOB_STATUS_PARSE       3
#define JOB_STATUS_EXTRACT     4
#define JOB_STATUS_SAVE        5
#define JOB_STATUS_PRINT       6
#define JOB_STATUS_COMPLETE    7

class CJob
{
private:
    static int jobId;

    int m_jobId;
    int m_jobStatus;

public:
    CJob();   
    virtual ~CJob();

    void SetJobId(int jobId);
    int GetJobId();
    void SetJobStatus(int jobStatus);
    int GetJobStatus();

    int InitJob(int jobStatus);
};

inline void CJob::SetJobId(int jobId)
{
    m_jobId = jobId;
}

inline int CJob::GetJobId()
{
    return m_jobId;
}

inline void CJob::SetJobStatus(int jobStatus)
{
    m_jobStatus = jobStatus;
}

inline int CJob::GetJobStatus()
{
    return m_jobStatus;
}
#endif // CJob_H
