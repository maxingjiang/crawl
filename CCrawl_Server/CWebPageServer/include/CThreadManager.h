#ifndef CTHEADMANAGER_H
#define CTHEADMANAGER_H

#include "CCollector.h"


#define THREAD_STATUS_RUNNING           0
#define THREAD_STATUS_STOP_EMERGENCY    1
#define THREAD_STATUS_STOP_NORMAL       2

#define THREAD_COLLECTOR_LIST_NOTFULL   0
#define THREAD_COLLECTOR_LIST_FULL      1

class CCollectorManager;
class CThread
{
public:
    CThread();
    virtual ~CThread();

    int AddCollector(CCollector* collector);
    int deleteCollector(CCollector* collector);

    pthread_t GetThreadId();

    void SetMaxCollectorCount(unsigned int maxCollectorCount);
    unsigned int GetMaxCollectorCount();

    int CreateThread();

    int GetListIsFullFlag();

    void SetCollectorMgr(CCollectorManager* collectorMgr);

public:
    pthread_t m_threadId;
    pthread_mutex_t m_collectorList_lock;
    vector<CCollector*> m_collectorList;
    int m_threadStopFlag;

    CCollectorManager* m_collectorMgr;

private:
    unsigned int m_maxCollectorCount;
    int m_listIsFullFlag;

    static void* ThreadWorker(void *arg);
};

class CThreadManager
{
public:
    CThreadManager();
    virtual ~CThreadManager();

    void SetMaxThreadCount(unsigned int maxThreadCount);
    unsigned int GetMaxThreadCount();

    int CreateThread(CCollectorManager *collectorMgr, CCollector *collector);
    int StopThread(int& stopModel);
    int AddCollector(CCollectorManager *collectorMgr, CCollector *collector);

    int IsExistAvailable(CThread **thread);

    CThread* FindThread(pthread_t threadId);

public:
    vector<CThread*> m_threadList;
    pthread_mutex_t m_threadList_lock;

private:
    unsigned int m_maxThreadCount;

};

#endif // CTHEADMANAGER_H
