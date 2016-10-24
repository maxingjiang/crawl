#include "CJobMgr.h"

CJobMgr::CJobMgr()
{
    m_jobList.clear();
}

CJobMgr::~CJobMgr()
{
    for(unsigned int i = 0; i < m_jobList.size(); i++)
    {
        if(m_jobList[i])
        {
            delete m_jobList[i];
            m_jobList[i] = NULL;
        }
    }
    m_jobList.clear();
}

int CJobMgr::SetJobList(vector<CJob*> job)
{
    try
    {
        for (vector<CJob*>::size_type i = 0;i < job.size();i++)
        {
            m_jobList.push_back(job[i]);
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
int CJobMgr::PushBackJob(CJob* job)
{
    try
    {
        m_jobList.push_back(job);
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

int CJobMgr::AddJobList(vector<CJob*> job)
{
    for(unsigned int i = 0; i < job.size(); i++)
    {
        m_jobList.push_back(job[i]);
    }
    return 0;
}
vector<CJob*> CJobMgr::GetJobList()
{
    return m_jobList;
}

int CJobMgr::ClearJobList()
{
    try
    {
        for (vector<CJob*>::size_type i = 0;i < m_jobList.size();i++)
        {
            CJob* tempJob = m_jobList[i];
            delete tempJob;
        }
        m_jobList.clear();
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

int CJobMgr::DeleteJob(int &jobId)
{
    try
    {
        for (vector<CJob*>::size_type i = 0;i < m_jobList.size();i++)
        {
            CJob* tempJob = m_jobList[i];
            if (tempJob->GetJobId() == jobId)
            {
                delete tempJob;
                m_jobList.erase(m_jobList.begin() + i);
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

int CJobMgr::CreateJob(int &jobStatus)
{
    CJob* job = new CJob();
    job->InitJob(jobStatus);

    PushBackJob(job);
    return 0;
}
