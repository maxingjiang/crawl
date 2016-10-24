#include "CTasks.h"

CTasks::CTasks()
{
    m_taskList.clear();
}

CTasks::~CTasks()
{
    m_taskList.clear();
}

int CTasks::SetTaskList(vector<CTask*> taskList)
{
    try
    {
        for (vector<CTask*>::size_type i = 0;i < taskList.size();i++)
        {
            m_taskList.push_back(taskList[i]);
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
int CTasks::AddTask(CTask* task)
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

int CTasks::AddTaskList(vector<CTask*> taskList)
{
    for(unsigned int i = 0; i < taskList.size(); i++)
    {
        m_taskList.push_back(taskList[i]);
    }
    return 0;
}
vector<CTask*> CTasks::GetTaskList()
{
    return m_taskList;
}

int CTasks::ClearTaskList()
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

int CTasks::DeleteTask(int &taskId)
{
    try
    {
        for (vector<CTask*>::size_type i = 0;i < m_taskList.size();i++)
        {
            CTask* tempTask = m_taskList[i];
            if (tempTask->GetTaskId() == taskId)
            {
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
