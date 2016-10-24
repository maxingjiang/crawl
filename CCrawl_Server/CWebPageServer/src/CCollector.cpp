#include <iostream>
#include "CCollector.h"
using namespace std;

CCollector::CCollector()
{
    m_crawl = NULL;
    m_ruleManager = NULL;
    m_workStatus = COLLECTOR_STATUS_INVALID;
	m_workModel = COLLECT_WORK_MODE_MAINURL;
	m_mainUrl = "";
    m_unexecuteUrl.clear();
    m_currentMission = NULL;
    m_currentWebPage = NULL;
}

CCollector::~CCollector()
{
	try
	{
        m_executeUrl.clear();
        m_unexecuteUrl.clear();
	}
	catch (int id)
	{
		cout << "Exception:" << id << endl;
	}
	catch (out_of_range &e)
	{
		cout << "an exception of out_of_range:" << e.what() << endl;
	}
	catch (bad_alloc &e)
	{
		cout << "an exception of an unexpected type:" << e.what() << endl;
	}
}

int CCollector::InitCollector(CCrawl* crawl, CMissionMgr* missionMgr, CRuleManager* ruleMgr, CMission* mission)
{
    SetCrawl(crawl);
    SetMissionMgr(missionMgr);
    SetRuleManager(ruleMgr);

    m_missions.AddMission(mission);
    m_currentMission = mission;

    SetWorkStatus(COLLECTOR_STATUS_INIT);
    return 0;
}

bool CCollector::SetUnexecuteUrl(vector<string> &unexecuteUrl)
{
	try
	{
        for (vector<string>::size_type i = 0;i < unexecuteUrl.size();i++)
		{
            m_unexecuteUrl.push_back(unexecuteUrl[i]);
		}
	}
	catch (int id)
	{
		cout << "Exception:" << id << endl;
		return false;
	}
	catch (out_of_range &e)
	{
		cout << "an exception of out_of_range:" << e.what() << endl;
		return false;
	}
	catch (bad_alloc &e)
	{
		cout << "an exception of an unexpected type:" << e.what() << endl;
		return false;
	}
	return true;
}
bool CCollector::AddUnexecuteUrl(string &unexecuteUrl)
{
	try
	{
        m_unexecuteUrl.push_back(unexecuteUrl);
	}
	catch (int id)
	{
		cout << "Exception:" << id << endl;
		return false;
	}
	catch (out_of_range &e)
	{
		cout << "an exception of out_of_range:" << e.what() << endl;
		return false;
	}
	catch (bad_alloc &e)
	{
		cout << "an exception of an unexpected type:" << e.what() << endl;
		return false;
	}
	return true;
}

void CCollector::AddUnexecuteUrl(vector<string> &unexecuteUrl)
{
    for(unsigned int i = 0; i < unexecuteUrl.size(); i++)
	{
		vector<string>::iterator ret;
        ret = std::find(m_unexecuteUrl.begin(), m_unexecuteUrl.end(), unexecuteUrl[i]);
        if(ret == m_unexecuteUrl.end())
		{
            m_unexecuteUrl.push_back(unexecuteUrl[i]);
		}
	}
  // m_unexecuteUrl.insert(m_unexecuteUrl.end(),childUrl.begin(),childUrl.end());
}
vector<string> CCollector::GetUnexecuteUrl()
{
    return m_unexecuteUrl;
}

bool CCollector::ClearUnexecuteUrl()
{
	try
	{
        m_unexecuteUrl.clear();
	}
	catch (int id)
	{
		cout << "Exception:" << id << endl;
		return false;
	}
	catch (out_of_range &e)
	{
		cout << "an exception of out_of_range:" << e.what() << endl;
		return false;
	}
	catch (bad_alloc &e)
	{
		cout << "an exception of an unexpected type:" << e.what() << endl;
		return false;
	}
	return true;
}

bool CCollector::DeleteUnexecuteUrl(string &unexecuteUrl)
{
	try
	{
        for (vector<string>::size_type i = 0;i < m_unexecuteUrl.size();i++)
		{
            if (m_unexecuteUrl[i] == unexecuteUrl)
			{
                m_unexecuteUrl.erase(m_unexecuteUrl.begin() + i);
			}
		}
	}
	catch (int id)
	{
		cout << "Exception:" << id << endl;
		return false;
	}
	catch (out_of_range &e)
	{
		cout << "an exception of out_of_range:" << e.what() << endl;
		return false;
	}
	catch (bad_alloc &e)
	{
		cout << "an exception of an unexpected type:" << e.what() << endl;
		return false;
	}
	return true;
}

bool CCollector::SetExecuteUrl(vector<string> &executeUrl)
{
    try
    {
        for (vector<string>::size_type i = 0;i < executeUrl.size();i++)
        {
            m_executeUrl.push_back(executeUrl[i]);
        }
    }
    catch (int id)
    {
        cout << "Exception:" << id << endl;
        return false;
    }
    catch (out_of_range &e)
    {
        cout << "an exception of out_of_range:" << e.what() << endl;
        return false;
    }
    catch (bad_alloc &e)
    {
        cout << "an exception of an unexpected type:" << e.what() << endl;
        return false;
    }
    return true;
}
bool CCollector::AddExecuteUrl(string &executeUrl)
{
    try
    {
        m_executeUrl.push_back(executeUrl);
    }
    catch (int id)
    {
        cout << "Exception:" << id << endl;
        return false;
    }
    catch (out_of_range &e)
    {
        cout << "an exception of out_of_range:" << e.what() << endl;
        return false;
    }
    catch (bad_alloc &e)
    {
        cout << "an exception of an unexpected type:" << e.what() << endl;
        return false;
    }
    return true;
}

void CCollector::AddExecuteUrl(vector<string> &executeUrl)
{
    for(unsigned int i = 0; i < executeUrl.size(); i++)
    {
        vector<string>::iterator ret;
        ret = std::find(m_executeUrl.begin(), m_executeUrl.end(), executeUrl[i]);
        if(ret == m_executeUrl.end())
        {
            m_executeUrl.push_back(executeUrl[i]);
        }
    }
}

vector<string> CCollector::GetExecuteUrl()
{
    return m_executeUrl;
}

bool CCollector::ClearExecuteUrl()
{
    try
    {
        m_executeUrl.clear();
    }
    catch (int id)
    {
        cout << "Exception:" << id << endl;
        return false;
    }
    catch (out_of_range &e)
    {
        cout << "an exception of out_of_range:" << e.what() << endl;
        return false;
    }
    catch (bad_alloc &e)
    {
        cout << "an exception of an unexpected type:" << e.what() << endl;
        return false;
    }
    return true;
}

bool CCollector::DeleteExecuteUrl(string &executeUrl)
{
    try
    {
        for (vector<string>::size_type i = 0;i < m_executeUrl.size();i++)
        {
            if (m_executeUrl[i] == executeUrl)
            {
                m_executeUrl.erase(m_executeUrl.begin() + i);
            }
        }
    }
    catch (int id)
    {
        cout << "Exception:" << id << endl;
        return false;
    }
    catch (out_of_range &e)
    {
        cout << "an exception of out_of_range:" << e.what() << endl;
        return false;
    }
    catch (bad_alloc &e)
    {
        cout << "an exception of an unexpected type:" << e.what() << endl;
        return false;
    }
    return true;
}

int CCollector::CrawlUrl(CCrawl* crawl, CWebPage* webPage)
{
    string url = webPage->GetUrl();
    crawl->setHttpRequestInit();
    int statuscode = crawl->GET_Html(url,"");
    if(statuscode == 200)
    {
        string body;
        crawl->getResponseBody(body);
        crawl->setHttpRequestCleanup();

        webPage->SetPageCode(body);
    }
    else
    {
        cout << "Collect \"" << url << "\" faild!" << "=====Code===>" << statuscode << endl;
    }
    return statuscode;
}

int CCollector::Run()
{
    CTask* task = m_tasks.GetFirstTask();
    if(!task)
    {
        cout << "Task is NULL" << endl;
        return COLLECTOR_MISSION_ERROR_NOTASK;
    }
    CJob* job = task->GetFirstJob();

    int returnCode = 0;
    int jobStatus = job->GetJobStatus();
    switch (jobStatus)
    {
        case JOB_STATUS_READY:
        {
            returnCode = InitWebPage();
            if(!returnCode)
            {
                task->DeleteJob(job);
            }
            break;
        }
        case JOB_STATUS_CRAWL:
        {
            returnCode = CrawlWebPage();
            if(!returnCode)
            {
                task->DeleteJob(job);
            }
            break;
        }
        case JOB_STATUS_MATCH_RULE:
        {
            returnCode = MatchRule();
            if(!returnCode)
            {
                task->DeleteJob(job);
            }
            break;
        }
        case JOB_STATUS_PARSE:
        {
            returnCode = ParseWebPage();
            if(!returnCode)
            {
                task->DeleteJob(job);
            }
            break;
        }
        case JOB_STATUS_EXTRACT:
        {
            returnCode = ExtractWebPage();
            if(!returnCode)
            {
                task->DeleteJob(job);
            }
            break;
        }
        case JOB_STATUS_SAVE:
        {
            returnCode = SaveWebPage();
            if(!returnCode)
            {
                task->DeleteJob(job);
            }
            break;
        }
        case JOB_STATUS_PRINT:
        {
            returnCode = PrintWebPage();
            if(!returnCode)
            {
                task->DeleteJob(job);
            }
            m_webPageMgr.ClearWebPageList();
            break;
        }
        case JOB_STATUS_COMPLETE:
        {
            returnCode = DeleteTask(task);
            if(!returnCode)
            {
                task->DeleteJob(job);
            }
            break;
        }
        default:
        {
            return COLLECTOR_JOB_ERROR_WRONG_STATUS;
        }
    }

    return returnCode;
}

int CCollector::CreateMission(string &mainUrl)
{
    CMission* mission = NULL;
    m_missionMgr->CreateMission(mainUrl, &mission, this);
    m_missions.AddMission(mission);
    return 0;
}

int CCollector::CreateTask(string &url)
{
    m_currentMission->CreateTask(url);
    return 0;
}

int CCollector::AddTask(CTask* task)
{
    m_tasks.AddTask(task);
    return 0;
}

int CCollector::InitWebPage()
{
    CTask* task = m_tasks.GetFirstTask();
    string url = task->GetUrl();

    m_webPageMgr.CreateWebPage(url);

    task->CreateJob(JOB_STATUS_CRAWL);

    return 0;
}

int CCollector::CrawlWebPage()
{
    CWebPage* webPage = NULL;
    webPage = m_webPageMgr.GetRunWebPage();
    if(!webPage)
    {
        return 1;
    }

    int returnCode = CrawlUrl(m_crawl, webPage);
    if(returnCode == 200)
    {
        AddJob(JOB_STATUS_MATCH_RULE);
        return 0;
    }
    else
    {
        return returnCode;
    }
}

int CCollector::MatchRule()
{
    CWebPage* webPage = NULL;
    webPage = m_webPageMgr.GetRunWebPage();
    if(!webPage)
    {
        return 1;
    }

    int range = 1;
    string fileName = "../conf/collectorRule/httpNewsIfengComRule.json";
    m_ruleManager->MatchRule(webPage, range, fileName);

    AddJob(JOB_STATUS_PARSE);

    return 0;
}

int CCollector::ParseWebPage()
{
    CWebPage* webPage = NULL;
    webPage = m_webPageMgr.GetRunWebPage();
    if(!webPage)
    {
        return 1;
    }
    webPage->Parse();

    AddJob(JOB_STATUS_EXTRACT);
    return 0;
}

int CCollector::ExtractWebPage()
{
    CWebPage* webPage = NULL;
    webPage = m_webPageMgr.GetRunWebPage();
    if(!webPage)
    {
        return 1;
    }
    m_ruleInterpreter.ExtractArticles(webPage);

    string nextUrl = webPage->GetNextPageUrl();
    if(nextUrl != "")
    {
        webPage->SetWebPageStatus(WEBPAGE_STATUS_COMPLETE);
        CreateTask(nextUrl);
        AddJob(JOB_STATUS_COMPLETE);
    }
    else
    {
        AddJob(JOB_STATUS_PRINT);
    }
    return 0;
}

int CCollector::SaveWebPage()
{
    return 0;
}

int CCollector::PrintWebPage()
{
    m_webPageMgr.Print();

    SetWorkStatus(COLLECTOR_STATUS_WORKDOWN);
    return 0;
}

int CCollector::DeleteTask(CTask* task)
{
    int taskId = task->GetTaskId();
    m_tasks.DeleteTask(taskId);
    m_currentMission->DeleteTask(task);
    return 0;
}

int CCollector::GetChildUrlFromWebPage(CWebPage* webPage)
{
    vector<string> urls;
    webPage->GetChildUrls(urls);
    AddUnexecuteUrl(urls);
    return 0;
}

int CCollector::AddJob(int jobStatus)
{
    CTask* task = m_tasks.GetFirstTask();
    task->CreateJob(jobStatus);
    return 0;
}

