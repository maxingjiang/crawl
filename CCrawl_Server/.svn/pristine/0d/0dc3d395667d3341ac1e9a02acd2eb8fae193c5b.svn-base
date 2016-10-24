#include "CThreadManager.h"
#include "CCollectorManager.h"

CThread::CThread()
{
    pthread_mutex_init(&m_collectorList_lock, NULL);
    m_collectorList.clear();
    m_listIsFullFlag = THREAD_COLLECTOR_LIST_NOTFULL;
    m_threadStopFlag = THREAD_STATUS_RUNNING;
    m_collectorMgr = NULL;
}

CThread::~CThread()
{
    pthread_mutex_lock(&m_collectorList_lock);
    m_collectorList.clear();
    pthread_mutex_unlock(&m_collectorList_lock);

    pthread_mutex_destroy(&m_collectorList_lock);
}

int CThread::CreateThread()
{
    int statusCode = pthread_create (&m_threadId, NULL, ThreadWorker,this);
    return statusCode;
}

int CThread::AddCollector(CCollector* collector)
{
    if(!m_listIsFullFlag)
    {
        pthread_mutex_lock(&m_collectorList_lock);
        m_collectorList.push_back(collector);
        if(m_collectorList.size() >= m_maxCollectorCount)
        {
            m_listIsFullFlag = THREAD_COLLECTOR_LIST_FULL;
        }
        pthread_mutex_unlock(&m_collectorList_lock);
    }
    else
    {
        return 1;
    }

    return 0;
}

int CThread::deleteCollector(CCollector* collector)
{
    CCollector* tempCollector = NULL;

    vector<CCollector*>::iterator it;
    for(it=m_collectorList.begin();it!=m_collectorList.end();)
    {
        tempCollector = *it;
        if(tempCollector == collector)
        {
            m_collectorList.erase(it);
            return 0;
        }
        else
        {
            it++;
        }
    }
    return 1;
}

pthread_t CThread::GetThreadId()
{
    return m_threadId;
}

void CThread::SetCollectorMgr(CCollectorManager* collectorMgr)
{
    m_collectorMgr = collectorMgr;
}

void CThread::SetMaxCollectorCount(unsigned int maxCollectorCount)
{
    m_maxCollectorCount = maxCollectorCount;
}

unsigned int CThread::GetMaxCollectorCount()
{
    return m_maxCollectorCount;
}

int CThread::GetListIsFullFlag()
{
    return m_listIsFullFlag;
}

void* CThread::ThreadWorker(void *arg)
{
    CThread *thread = (CThread*)arg;
    if(thread)
    {
        while(thread->m_threadStopFlag != THREAD_STATUS_STOP_EMERGENCY)
        {
            pthread_mutex_lock(&(thread->m_collectorList_lock));
            for(unsigned int i = 0; i < thread->m_collectorList.size();i++)
            {
                CCollector* collector = thread->m_collectorList[i];

                collector->Run();

                if(collector->GetWorkStatus() == COLLECTOR_STATUS_WORKDOWN)
                {
                    thread->deleteCollector(collector);
                    if(thread->m_collectorList.empty())
                    {
                        break;
                    }
                }
            }
            pthread_mutex_unlock(&(thread->m_collectorList_lock));

            if(thread->m_threadStopFlag == THREAD_STATUS_STOP_NORMAL && thread->m_collectorList.empty())
            {
                break;
            }
            sleep(1);
        }
        pthread_exit(0);
        cout << "thread stop !!!" << endl;
    }
    else
    {
        pthread_exit(0);
    }
    return NULL;
}

CThreadManager::CThreadManager()
{
    pthread_mutex_init(&m_threadList_lock, NULL);
    m_threadList.clear();
}

CThreadManager::~CThreadManager()
{
    pthread_mutex_lock(&m_threadList_lock);
    for(unsigned int i = 0; i < m_threadList.size(); i++)
    {
        if(m_threadList[i] != NULL)
        {
            delete m_threadList[i];
            m_threadList[i] = NULL;
        }
    }
    m_threadList.clear();
    pthread_mutex_unlock(&m_threadList_lock);

    pthread_mutex_destroy(&m_threadList_lock);
}

void CThreadManager::SetMaxThreadCount(unsigned int maxThreadCount)
{
    m_maxThreadCount = maxThreadCount;
}

unsigned int CThreadManager::GetMaxThreadCount()
{
    return m_maxThreadCount;
}

int CThreadManager::IsExistAvailable(CThread **thread)
{
    pthread_mutex_lock(&m_threadList_lock);
    for(unsigned int i = 0; i < m_threadList.size(); i++)
    {
        CThread *tempThread = m_threadList[i];
        if(!tempThread->GetListIsFullFlag())
        {
            *thread = tempThread;
            pthread_mutex_unlock(&m_threadList_lock);
            return 1;
        }
    }
    pthread_mutex_unlock(&m_threadList_lock);
    return 0;
}

int CThreadManager::StopThread(int& stopModel)
{
    for(unsigned int i = 0; i < m_threadList.size(); i++)
    {
        CThread* thread = m_threadList[i];
        thread->m_threadStopFlag = stopModel;
        pthread_join (thread->m_threadId, NULL);
    }

    return 0;
}

CThread* CThreadManager::FindThread(pthread_t threadId)
{
    CThread* thread = NULL;
    CThread* tempThread = NULL;
    pthread_mutex_lock(&m_threadList_lock);
    for(unsigned int i = 0; i < m_threadList.size(); i++)
    {
        tempThread = m_threadList[i];
        if(tempThread->GetThreadId() == threadId)
        {
            thread = tempThread;
            pthread_mutex_unlock(&m_threadList_lock);
            return thread;
        }
    }
    pthread_mutex_unlock(&m_threadList_lock);
    return thread;
}

int CThreadManager::CreateThread(CCollectorManager *collectorMgr,CCollector *collector)
{
    CThread *thread = new CThread();
    thread->SetMaxCollectorCount(1);
    thread->AddCollector(collector);
    thread->SetCollectorMgr(collectorMgr);

    int statusCode = thread->CreateThread();

    if(!statusCode)
    {
        pthread_mutex_lock(&m_threadList_lock);
        m_threadList.push_back(thread);
        pthread_mutex_unlock(&m_threadList_lock);
    }
    else
    {
        delete thread;
    }
    return statusCode;
}

int CThreadManager::AddCollector(CCollectorManager *collectorMgr, CCollector *collector)
{
    return 0;
}


