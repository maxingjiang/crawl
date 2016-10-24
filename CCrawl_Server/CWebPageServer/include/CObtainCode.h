#pragma once
#include <map>
#include "include.h"
#include "json/json.h"

class CTag
{

public:
    int m_count;
    string m_tag;
    map<string, string> m_attributes;

};

//提取代码类
class CObtainCode
{

public:
    vector<CTag> m_tagList;


	CObtainCode();
	virtual ~CObtainCode();

    int readJson(Json::Value &root);
    int writeJson(Json::Value &root);
};

inline CObtainCode::CObtainCode()
{
   m_tagList.clear();
}
inline CObtainCode::~CObtainCode()
{
    m_tagList.clear();
}

