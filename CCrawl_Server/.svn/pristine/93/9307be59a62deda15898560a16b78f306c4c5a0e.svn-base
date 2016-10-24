#pragma once
#include "CTask.h"

class CTasks
{
private:
    vector<CTask*> m_taskList;

public:
    CTasks();
    virtual ~CTasks();

    unsigned int GetTaskListSize();
    int SetTaskList(vector<CTask*> taskList);
    int AddTask(CTask* task);
    int AddTaskList(vector<CTask*> taskList);
    vector<CTask*> GetTaskList();
    CTask* GetTask(unsigned int &i);
    CTask* GetFirstTask() const;
    bool IsTaskListEmpty()const;
    int DeleteTask(int &taskId);
    int ClearTaskList();
};

inline unsigned int CTasks::GetTaskListSize()
{
    return m_taskList.size();
}

inline CTask* CTasks::GetTask(unsigned int &i)
{
    return m_taskList[i];
}

inline CTask* CTasks::GetFirstTask() const
{
    return m_taskList.front();
}

inline bool CTasks::IsTaskListEmpty()const
{
    return m_taskList.empty();
}
