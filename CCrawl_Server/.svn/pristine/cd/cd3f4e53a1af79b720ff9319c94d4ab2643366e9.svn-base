#include "CTaskManager.h"
#include "CCollector.h"
#include <iostream>
using namespace std;

CTaskManager::CTaskManager()
{
    m_taskList.clear();
}

CTaskManager::~CTaskManager()
{
    for(unsigned int i = 0; i < m_taskList.size(); i++)
    {
        if(m_taskList[i])
        {
            delete m_taskList[i];
            m_taskList[i] = NULL;
        }
    }
    m_taskList.clear();
}

int CTaskManager::SetTaskList(vector<CTask*> task)
{
    try
    {
        for (vector<CTask*>::size_type i = 0;i < task.size();i++)
        {
            m_taskList.push_back(task[i]);
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
int CTaskManager::AddTask(CTask* task)
{
    try
    {
        m_taskList.push_back(task);
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

int CTaskManager::AddTaskList(vector<CTask*> task)
{
    for(unsigned int i = 0; i < task.size(); i++)
    {
        m_taskList.push_back(task[i]);
    }
    return 0;
}
vector<CTask*> CTaskManager::GetTaskList()
{
    return m_taskList;
}

int CTaskManager::ClearTaskList()
{
    try
    {
        for (vector<CTask*>::size_type i = 0;i < m_taskList.size();i++)
        {
            CTask* tempTask = m_taskList[i];
            delete tempTask;
        }
        m_taskList.clear();
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

int CTaskManager::DeleteTask(int taskId)
{
    try
    {
        for (vector<CTask*>::size_type i = 0;i < m_taskList.size();i++)
        {
            CTask* tempTask = m_taskList[i];
            if (tempTask->GetTaskId() == taskId)
            {
                delete tempTask;
                m_taskList.erase(m_taskList.begin() + i);
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

int CTaskManager::CreateTask(string &url,CTask** task)
{
    (*task) = new CTask();
    (*task)->InitTask(url);
    AddTask(*task);
    return 0;
}


