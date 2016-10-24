#pragma once
#include "include.h"
//文章类
class CArticle
{
private:
	string m_title;
	string m_content;
	string m_url;
	string m_author;
	string m_date;
	string m_nextPageUrl;
	string m_loginName;

public:
	CArticle();
	virtual ~CArticle();

	bool operator==(const CArticle&)const;

    void SetTitle(string &title);
	string GetTitle()const;

    void SetContent(string &content);
	string GetContent()const;

    void SetUrl(string &url);
	string GetUrl()const;

    void SetAuthor(string &author);
	string GetAuthor()const;

    void SetDate(string &date);
	string GetDate()const;

    void SetNextPageUrl(string &nextPageUrl);
	string GetNextPageUrl()const;

    void SetLoginName(string &loginName);
	string GetLoginName()const;

};

inline bool CArticle::operator==(const CArticle &article)const
{
	if (article.m_title != m_title)
	{
		return false;
	}
	else if (article.m_url != m_url)
	{
		return false;
	}
	else if (article.m_author != m_author)
	{
		return false;
	}
	else if (article.m_date != m_date)
	{
		return false;
	}
	else if (article.m_loginName != m_loginName)
	{
		return false;
	}
	else
	{
		return true;
	}
}

inline void CArticle::SetTitle(string &title)
{
	m_title = title;
}
inline string CArticle::GetTitle()const
{
	return m_title;
}

inline void CArticle::SetContent(string &content)
{
	m_content = content;
}
inline string CArticle::GetContent()const
{
	return m_content;
}

inline void CArticle::SetUrl(string &url)
{
	m_url = url;
}
inline string CArticle::GetUrl()const
{
	return m_url;
}

inline void CArticle::SetAuthor(string &author)
{
	m_author = author;
}
inline string CArticle::GetAuthor()const
{
	return m_author;
}

inline void CArticle::SetDate(string &date)
{
	m_date = date;
}
inline string CArticle::GetDate()const
{
	return m_date;
}

inline void CArticle::SetNextPageUrl(string &nextPageUrl)
{
	m_nextPageUrl = nextPageUrl;
}
inline string CArticle::GetNextPageUrl()const
{
	return m_nextPageUrl;
}

inline void CArticle::SetLoginName(string &loginName)
{
	m_loginName = loginName;
}
inline string CArticle::GetLoginName()const
{
	return m_loginName;
}
