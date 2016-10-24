#include "CWebPageMgr.h"


CWebPageMgr::CWebPageMgr()
{
    m_webPageList.clear();
}

CWebPageMgr::~CWebPageMgr()
{
    for(unsigned int i = 0; i < m_webPageList.size(); i++)
    {
        if(m_webPageList[i])
        {
            delete m_webPageList[i];
            m_webPageList[i] = NULL;
        }
    }
    m_webPageList.clear();
}

int CWebPageMgr::CreateWebPage(int webPageId, string& url)
{
    CWebPage* webpage = new CWebPage(webPageId, url);
    if(webpage)
    {
        m_webPageList.push_back(webpage);
        return 0;
    }
    else
    {
        return 1;
    }
}

int CWebPageMgr::CreateWebPage(string& url)
{
    CWebPage* webpage = new CWebPage(url);
    if(webpage)
    {
        m_webPageList.push_back(webpage);
        return 0;
    }
    else
    {
        return 1;
    }
}

int CWebPageMgr::SetWebPageList(vector<CWebPage*> webpageList)
{
    try
    {
        for (vector<CWebPage*>::size_type i = 0;i < webpageList.size();i++)
        {
            m_webPageList.push_back(webpageList[i]);
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
int CWebPageMgr::AddWebPage(CWebPage* webpage)
{
    try
    {
        m_webPageList.push_back(webpage);
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

int CWebPageMgr::AddWebPageList(vector<CWebPage*> webpageList)
{
    for(unsigned int i = 0; i < webpageList.size(); i++)
    {
        m_webPageList.push_back(webpageList[i]);
    }
    return 0;
}
vector<CWebPage*> CWebPageMgr::GetWebPageList()
{
    return m_webPageList;
}

int CWebPageMgr::ClearWebPageList()
{
    try
    {
        for (vector<CWebPage*>::size_type i = 0;i < m_webPageList.size();i++)
        {
            CWebPage* tempWebpage = m_webPageList[i];
            delete tempWebpage;
        }
        m_webPageList.clear();
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

int CWebPageMgr::DeleteWebPage(int webPageId)
{
    try
    {
        for (vector<CWebPage*>::size_type i = 0;i < m_webPageList.size();i++)
        {
            CWebPage* tempWebPage = m_webPageList[i];
            if (tempWebPage->GetWebPageId() == webPageId)
            {
                delete tempWebPage;
                m_webPageList.erase(m_webPageList.begin() + i);
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

CWebPage* CWebPageMgr::GetRunWebPage()
{
    CWebPage* webpage = NULL;
    for(unsigned int i = 0; i < m_webPageList.size(); i++)
    {
        CWebPage* tempWebPage = m_webPageList[i];
        int webPageStatus = tempWebPage->GetWebPageStatus();
        if(webPageStatus == WEBPAGE_STATUS_READY || webPageStatus == WEBPAGE_STATUS_RUNNING)
        {
            webpage = tempWebPage;
            break;
        }
    }
    return webpage;
}

int CWebPageMgr::Print()
{
    string content = "";
    for(unsigned int i = 0; i < m_webPageList.size(); i++)
    {
        CWebPage* webpage = m_webPageList[i];
        cout << __FILE__ << __LINE__ << "==============Url==>" << webpage->GetUrl() << endl;

        for(unsigned int j = 0; j < webpage->m_articlesList.size(); j++)
        {
            CArticle article = webpage->m_articlesList[j];
            content = content + article.GetContent();
        }

    }
    cout << __FILE__ << __LINE__ << "==============Tile==>" << m_webPageList[0]->GetTitle() << endl;
    cout << __FILE__ << __LINE__ << "==============Content==>" << endl << content << endl;
    return 0;
}
