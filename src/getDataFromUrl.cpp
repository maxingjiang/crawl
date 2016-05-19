
#include <iostream>
#include "getDataFromUrl.h"

string getBusInfoByUrl(CURL *curl, string &Url)
{
    crawl cr;
    cr.clear();

    curl=curl_easy_init();
    struct curl_slist *headers = NULL;
    std::string filename = "conf/request.conf";
    readConf rd(filename);
    rd.readrequest();
    std::vector<std::string>::iterator iter = rd.m_requestconf.begin();
    //cout<<"request header===>: \n";
    for(; iter != rd.m_requestconf.end(); iter++)
    {
        //cout<<*iter<<endl;
        headers = curl_slist_append(headers, (*iter).c_str());
    }
    /*
    filename = "conf/cookie.conf";
    readConf rd1(filename);
    rd1.readrequest();
    std::vector<std::string>::iterator itercookie = rd1.m_requestconf.begin();
    //cout<<"cookie header===>: \n";
    std::string cookies = "Cookie: ";
    for(; itercookie != rd1.m_requestconf.end(); itercookie++)
    {
        //cout<<*itercookie<<endl;
        cookies = cookies + *itercookie;
    }
    //cout<<"cookie header end===>: \n";
    headers = curl_slist_append(headers, cookies.c_str());
	*/
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, Url.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    char buffer[1000000] = {0x0};
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, crawl::write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, crawl::header_callback);
    //curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    //std::cout<<"head===>\n"<<cr.m_head_buf.size()<<" :\n"<<cr.m_head_buf<<std::endl;
    //std::cout<<"body===>\n"<<buffer<<std::endl;
    return buffer;
}
