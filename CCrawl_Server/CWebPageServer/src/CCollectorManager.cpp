#include <iostream>
#include <iomanip>
#include "CCollectorManager.h"
#include <time.h>

CCollectorManager::CCollectorManager()
{
}
CCollectorManager::~CCollectorManager()
{
	size_t i;
	for (i = 0; i < m_collectorList.size(); i++)
	{
        if(m_collectorList[i] != NULL)
            delete m_collectorList[i];
	}
	m_collectorList.clear();
}

int CCollectorManager::InitCollectorMgr(int threadPoolCount)
{
    return 0;
}

CCollector* CCollectorManager::CreateCollector(string &url)
{
    CCollector *collector = new CCollector();

    CCrawl* crawl = m_crawlMgr.createCrawl();
    crawl->setRequestHeaders(m_requestHeaders);
    crawl->setProxy(m_proxy);

    CMission* mission = NULL;
    m_missionMgr.CreateMission(url, &mission, collector);

    collector->InitCollector(crawl, &m_missionMgr, &m_ruleManager, mission);

    m_collectorList.push_back(collector);
	return collector;
}

CCollector* CCollectorManager::GetCollector(string url) const
{
    size_t i;
    for (i = 0; i < m_collectorList.size(); i++)
    {
        if (m_collectorList[i]->GetMainUrl() == url)
        {
            return m_collectorList[i];
        }
    }
    return NULL;
}

int CCollectorManager::CreateCollectorMission(string &url)
{
    CCollector* collector = NULL;
    collector = CreateCollector(url);

    CThread* thread = NULL;

    static int threadCount = 0;

    if(!m_threadMgr.IsExistAvailable(&thread))
    {
        if(!m_threadMgr.CreateThread(this, collector))
        {
            cout << "CreateThread =====>" << "Thread NUM : " << ++threadCount << endl;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if(!thread->AddCollector(collector))
        {
            cout << "AddCollector =====>" << "Thread NUM : " << threadCount << endl;
        }
        else
        {
            return 2;
        }

    }
    return 0;
}

int CCollectorManager::LoadCollectorMission()
{

    return 0;
}

int CCollectorManager::StopAllCollectorMission(int& stopModel)
{
    m_threadMgr.StopThread(stopModel);
    return 0;
}
