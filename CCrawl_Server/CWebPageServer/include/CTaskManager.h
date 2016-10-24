#ifndef CTaskMANAGER_H
#define CTaskMANAGER_H

#include "include.h"
#include "CTask.h"

class CCollector;

class CTaskManager
{
private:
    vector<CTask*> m_taskList;

public:
    CTaskManager();
    virtual ~CTaskManager();

    unsigned int GetTaskListSize();
    int SetTaskList(vector<CTask*> task);
    int AddTask(CTask* task);
    int AddTaskList(vector<CTask*> task);
    vector<CTask*> GetTaskList();
    CTask* GetTask(unsigned int i);
    CTask* GetFirstTask() const;
    bool IsTaskListEmpty()const;
    int DeleteTask(int taskId);
    int ClearTaskList();

    int CreateTask(string &url, CTask** task);
};
inline unsigned int CTaskManager::GetTaskListSize()
{
    return m_taskList.size();
}

inline CTask* CTaskManager::GetTask(unsigned int i)
{
    return m_taskList[i];
}

inline CTask* CTaskManager::GetFirstTask() const
{
    return m_taskList.front();
}

inline bool CTaskManager::IsTaskListEmpty()const
{
    return m_taskList.empty();
}

#endif // CTaskMANAGER_H
