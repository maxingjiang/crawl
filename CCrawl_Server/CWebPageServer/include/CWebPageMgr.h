#pragma once
#include "CWebPage.h"

class CWebPageMgr
{
private:
    vector<CWebPage*> m_webPageList;		//网页

public:
    CWebPageMgr();
    virtual ~CWebPageMgr();

    unsigned int GetWebPageListSize();
    int SetWebPageList(vector<CWebPage*> webPage);
    int AddWebPage(CWebPage* task);
    int AddWebPageList(vector<CWebPage*> webPage);
    vector<CWebPage*> GetWebPageList();
    CWebPage* GetWebPage(unsigned int i);
    CWebPage* GetFirstWebPage() const;
    bool IsWebPageListEmpty()const;
    int DeleteWebPage(int webPageId);
    int ClearWebPageList();

    int CreateWebPage(int webPageId, string& url);
    int CreateWebPage(string& url);

    CWebPage* GetRunWebPage();

    int Print();
};

inline unsigned int CWebPageMgr::GetWebPageListSize()
{
    return m_webPageList.size();
}

inline CWebPage* CWebPageMgr::GetWebPage(unsigned int i)
{
    return m_webPageList[i];
}

inline CWebPage* CWebPageMgr::GetFirstWebPage() const
{
    return m_webPageList.front();
}

inline bool CWebPageMgr::IsWebPageListEmpty()const
{
    return m_webPageList.empty();
}
