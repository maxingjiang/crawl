#include "CMission.h"
#include "CCollector.h"

int CMission::missionId = -1;

CMission::CMission()
{
    m_missionId = ++missionId;
    m_missionStatus = MISSION_STATUS_INVALID;
    m_mainUrl = "";
    m_collector = NULL;
}

CMission::~CMission()
{

}

int CMission::initMission(string &mainUrl, CCollector* collector)
{
    m_mainUrl = mainUrl;
    m_collector = collector;

    CreateTask(mainUrl);

    m_missionStatus = MISSION_STATUS_READY;
    return 0;
}

int CMission::CreateTask(string &mainUrl)
{
    CTask* task = NULL;
    m_taskMgr.CreateTask(mainUrl,&task);
    m_collector->AddTask(task);
    return 0;
}
int CMission::DeleteTask(CTask* task)
{
    int taskId = task->GetTaskId();
    m_taskMgr.DeleteTask(taskId);
    return 0;
}

CTask* CMission::GetTask()
{
    CTask* task = NULL;
    task = m_taskMgr.GetFirstTask();
    return task;
}
