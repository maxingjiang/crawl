#include "CObtainCode.h"

int CObtainCode::readJson(Json::Value &root)
{
    for(unsigned int i = 0; i < root.size(); i++)
    {
        Json::Value parentNode = root[i];

        CTag tag;
        string attrName = "";
        string value = "";

        tag.m_count = parentNode["count"].asInt();
        tag.m_tag = parentNode["tag"].asString();

        Json::Value Node = parentNode["attributes"];
        for (unsigned int j = 0; j < Node.size(); j++)
        {
            Json::Value childNode = Node[j];

            attrName = childNode["attrName"].asString();
            value = childNode["value"].asString();

            tag.m_attributes.insert(pair<string,string>(attrName, value));
        }
        m_tagList.push_back(tag);
    }
    return 0;
}
int CObtainCode::writeJson(Json::Value &root)
{
    Json::Value item;
    Json::Value childNode;
    Json::Value parentNode;

    for(unsigned int i = 0; i < m_tagList.size(); i++)
    {
        CTag tag = m_tagList[i];

        parentNode["count"] = tag.m_count;
        parentNode["tag"] = tag.m_tag;

        map<string,string>::iterator it;

        for(it = tag.m_attributes.begin(); it != tag.m_attributes.end(); ++it)
        {
            item["attrName"] = it->first;
            item["value"]   = it->second;
            childNode.append(item);
            item.clear();
        }

        parentNode["attributes"] = childNode;
        childNode.clear();

        root.append(parentNode);
    }
    return 0;
}
