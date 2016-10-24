
#include <iostream>
#include <string.h>

#include "CResponseBody.h"
#include "common.h"
#include "split.h"


CResponseBody::CResponseBody()
{
	m_url.clear();
	m_responseHeader.clear();
	m_responseBody.clear();
}

CResponseBody::~CResponseBody()
{
	m_url.clear();
	m_responseHeader.clear();
	m_responseBody.clear();
}

string CResponseBody::getResponseHeader()
{
	return m_responseHeader;
}

string CResponseBody::getResponseBody()
{
	return m_responseBody;
}

string CResponseBody::getUrlData(const string &url, const vector<string> &headersparames, const string &postParames, const string &ip, int port, bool setproxy)
{
	CURL *m_curl = curl_easy_init();

	if(url.length() >= URL_LENGTH || url.length() <= 1)
	{
		m_responseHeader = "";
		m_responseBody = "";
		m_url = url;
		return m_responseBody;
	}
    struct curl_slist *headers = NULL;
    vector<string>::const_iterator iter = headersparames.begin();
    for(; iter != headersparames.end(); iter++)
    {
        //cout<<*iter<<endl;
        headers = curl_slist_append(headers, (*iter).c_str());
    }
    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);
    if(setproxy == true)
    {
        curl_easy_setopt(m_curl, CURLOPT_PROXY, ip.c_str());
        curl_easy_setopt(m_curl, CURLOPT_PROXYPORT, port);
    }

    curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 2L);
    curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "gzip");
    if(!postParames.empty())
    {
    	cout<<"url======>"<<url.c_str()<<endl;
    	cout<<"post======>"<<postParames.c_str()<<endl;
    	curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, postParames.c_str());
    	//curl_easy_setopt(m_curl, CURLOPT_POST, 1);
    	curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "POST");
    }

    string buffer_header;
    buffer_header.clear();
    curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, namespace_split::write_header);
    curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &buffer_header);
    //curl_easy_setopt(m_curl, CURLOPT_NOBODY, 1L); //not body
    curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "HEAD");
    curl_easy_perform(m_curl);
    cout<<"header===>\n"<<buffer_header<<endl;
    char *contype = NULL;
    string contenttype;
    curl_easy_getinfo(m_curl, CURLINFO_CONTENT_TYPE, &contype);

    if(contype == NULL)
    {
		m_responseHeader = "";
		m_responseBody = "";
		m_url = url;
		return m_responseBody;
    }
    contenttype = contype;
    if(contenttype.find("text", 0) != 0)
    {
		m_responseHeader = "";
		m_responseBody = "";
		m_url = url;
		return m_responseBody;
    }
    string buffer_data;
    buffer_data.clear();
    buffer_header.clear();
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, namespace_split::write_data);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &buffer_data);
    //curl_easy_setopt(m_curl, CURLOPT_NOBODY, 0L);
    curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_perform(m_curl);
    curl_easy_cleanup(m_curl);

    cout<<"header===>\n"<<buffer_header<<endl;
    m_responseHeader = buffer_header;
    m_responseBody = buffer_data;
    //cout<<"body===>\n"<<buffer_data<<endl;
    m_url = url;
    return buffer_data;
}

/*
string CResponseBody::getUrlData(string &Url, vector<string> &headersparames, string &ip, int port, bool setproxy)
{
	if(Url.length() >= URL_LENGTH || Url.length() <= 1)
	{
		m_responseHeader = "";
		m_responseBody = "";
		m_url = Url;
		return m_responseBody;
	}
	m_curl=curl_easy_init();
    struct curl_slist *headers = NULL;
    vector<string>::iterator iter = headersparames.begin();
    for(; iter != headersparames.end(); iter++)
    {
        //cout<<*iter<<endl;
        headers = curl_slist_append(headers, (*iter).c_str());
    }
    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);
    if(setproxy == true)
    {
        curl_easy_setopt(m_curl, CURLOPT_PROXY, ip.c_str());
        curl_easy_setopt(m_curl, CURLOPT_PROXYPORT, port);
    }
    curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(m_curl, CURLOPT_URL, Url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 2L);
    curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "gzip");

    string buffer_header;
    buffer_header.clear();
    curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, Csplit::write_header);
    curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &buffer_header);
    curl_easy_setopt(m_curl, CURLOPT_NOBODY, 1L); //not body
    curl_easy_perform(m_curl);
    //cout<<"header===>\n"<<buffer_header<<endl;
    char *contype = NULL;
    string contenttype;
    curl_easy_getinfo(m_curl, CURLINFO_CONTENT_TYPE, &contype);

    if(contype == NULL)
    {
		m_responseHeader = "";
		m_responseBody = "";
		m_url = Url;
		return m_responseBody;
    }
    contenttype = contype;
    if(contenttype.find("text", 0) != 0)
    {
		m_responseHeader = "";
		m_responseBody = "";
		m_url = Url;
		return m_responseBody;
    }
    //sleep(1);
    string buffer_data;
    buffer_data.clear();
    buffer_header.clear();
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, Csplit::write_data);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &buffer_data);
    curl_easy_setopt(m_curl, CURLOPT_NOBODY, 0L);
    curl_easy_perform(m_curl);

    curl_easy_cleanup(m_curl);

    //cout<<"header===>\n"<<buffer_header<<endl;
    m_responseHeader = buffer_header;
    m_responseBody = buffer_data;
    cout<<"body===>"<<buffer_data.length()<<endl;
    m_url = Url;
    return buffer_data;
}
*/
/*
string CResponseBody::testgetUrlData(string &Url)
{

	m_curl = curl_easy_init();
    struct curl_slist *headers = NULL;
    string filename = "header.txt";
    const int LINE_LENGTH = 1024;
    char str[LINE_LENGTH];
    vector<string> headerssrc;
    ifstream fin(filename.c_str());
    while( fin.getline(str,LINE_LENGTH) != NULL)
    {
    	headerssrc.push_back(str);
    }
    fin.close();
    vector<string>::iterator iter = headerssrc.begin();
    for(; iter != headerssrc.end(); iter++)
    {
        //cout<<*iter<<endl;
        headers = curl_slist_append(headers, (*iter).c_str());
    }
    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(m_curl, CURLOPT_URL, Url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 2L);
    string buffer_data;
    buffer_data.clear();
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, Csplit::write_data);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &buffer_data);
    string buffer_header;
    buffer_header.clear();
    curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, Csplit::write_header);
    curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &buffer_header);
    //curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); //not body
    curl_easy_perform(m_curl);
    curl_easy_cleanup(m_curl);
   // curl_slist_free_all(headers);
    //cout<<"header===>\n"<<buffer_header<<endl;
    m_responseBody = buffer_data;
    //std::cout<<"body===>\n"<<buffer_data<<std::endl;
    m_url = Url;
    return buffer_data;
}
*/
