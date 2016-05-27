/*
 * test.cpp
 *
 *  Created on: May 17, 2016
 *      Author: mxj
 */
#include "test.h"

int Test::postUrl()
{
    std:;cout<<"post===>\n";
    CURL *curl;
    CURLcode res;
    FILE *fp;
    if ((fp = fopen("a.txt", "w")) == NULL)
        return 0;
    curl = curl_easy_init();
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_POST, 1L);
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");
        curl_easy_setopt(curl, CURLOPT_PROXY, "60.191.174.13");
        curl_easy_setopt(curl, CURLOPT_PROXYPORT, 3128);
        //curl_easy_setopt(curl, CURLOPT_POST, 1L);
        //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"cuisineBookId\":\"100\"}");
        curl_easy_setopt(curl, CURLOPT_URL, "http://222.85.139.244:1001/BusService/Require_AllRouteData/?TimeStamp=1");
        //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"userid\":\"101\",\"tel\":\"18612304173\",\"password\":\"123456a\"}");
        //curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.199.128:8080/api/user/login");
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return 1;
}

int Test::getCCT()
{
    CURL *curl;
    CURLcode res;
    FILE *fp;
    crawl cr;
    cr.clear();
    if ((fp = fopen("post.html", "w")) == NULL)
        return 0;
    curl = curl_easy_init();
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_POST, 1L);
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");
        //curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_URL, "http://222.85.139.244:1001/BusService/Require_AllRouteData/?TimeStamp=1");
        //curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        char buffer_header[10000] = {0x0};
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, crawl::header_callback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, buffer_header);
	    //curl_easy_setopt(curl, CURLOPT_HEADERDATA, fp);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        std::cout<<"head===>\n"<<buffer_header<<std::endl;
        std::vector<std::string> iter_cookie = cr.split_response_cookie(string(buffer_header), "Set-Cookie:");
        std::vector<std::string>::iterator iter = iter_cookie.begin();
        FILE *pcookie;
        if ((pcookie = fopen("../conf/cookie.conf", "w")) == NULL)
            return 0;
        for(; iter != iter_cookie.end(); iter++)
        {
            std::vector<std::string> cookieidsline = cr.split(*iter, ";");
            std::string cookieidid = (*cookieidsline.begin()).substr(strlen("Set-Cookie: "), (*cookieidsline.begin()).length() - strlen("Set-Cookie: "));
            cout<<cookieidid<<endl;
            fprintf(pcookie, "%s\n",cookieidid.c_str());
        }
        fclose(pcookie);
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return 1;
}

int Test::getUrl()
{
    CURL *curl;
    crawl cr;
    cr.clear();
    curl_global_init(CURL_GLOBAL_ALL);
    curl=curl_easy_init();
    struct curl_slist *headers = NULL;
    std::string filename = "../conf/request.conf";
    readConf rd(filename);
    rd.readrequest();
    std::vector<std::string>::iterator iter = rd.m_requestconf.begin();
    cout<<"request header===>: \n";
    for(; iter != rd.m_requestconf.end(); iter++)
    {
        cout<<*iter<<endl;
        //headers = curl_slist_append(headers, (*iter).c_str());
    }

    filename = "../conf/cookie.conf";
    readConf rd1(filename);
    rd1.readrequest();
    std::vector<std::string>::iterator itercookie = rd1.m_requestconf.begin();
    cout<<"cookie header===>: \n";
    std::string cookies = "Cookie: ";
    for(; itercookie != rd1.m_requestconf.end(); itercookie++)
    {
        cout<<*itercookie<<endl;
        cookies = cookies + *itercookie;
    }
    cout<<"cookie header end===>: \n";
    headers = curl_slist_append(headers, cookies.c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, "http://user.qzone.qq.com/994513645");
    //curl_easy_setopt(curl, CURLOPT_URL, "http://home.cnblogs.com/set/account/");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    //curl_easy_setopt(curl, CURLOPT_URL, "http://www.douguo.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, crawl::write_data);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, crawl::header_callback);
    //curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_perform(curl);
    //cr.get_body("logo.png");
    curl_easy_cleanup(curl);
    std::cout<<"head===>\n"<<cr.m_head_buf.size()<<" :\n"<<cr.m_head_buf<<std::endl;
    std::cout<<"body===>\n"<<cr.m_data_buf.size()<<" :\n"<<cr.m_data_buf<<std::endl;
    return 0;
}

void Test::setBusInfo()
{
	CURL *curl;
    crawl cr;
    cr.clear();
    curl_global_init(CURL_GLOBAL_ALL);
    curl=curl_easy_init();
    //curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, "http://222.85.139.244:1001/BusService/Require_AllRouteData/?TimeStamp=1");
    //curl_easy_setopt(curl, CURLOPT_URL, "http://home.cnblogs.com/set/account/");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    //curl_easy_setopt(curl, CURLOPT_URL, "http://www.douguo.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, crawl::write_data);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, crawl::header_callback);
    //curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_perform(curl);
    //cr.get_body("logo.png");
    curl_easy_cleanup(curl);
    std::cout<<"head===>\n"<<cr.m_head_buf.size()<<" :\n"<<cr.m_head_buf<<std::endl;
    std::cout<<"body===>\n"<<cr.m_data_buf.size()<<" :\n"<<cr.m_data_buf<<std::endl;
}

string Test::testgetBusInfoByUrl(CURL *curl, string &Url)
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
    curl_easy_setopt(curl, CURLOPT_PROXY, "220.197.219.150");
    curl_easy_setopt(curl, CURLOPT_PROXYPORT, 9083);
    char buffer[1000000] = {0x0};
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, crawl::write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
    char buffer1[1000000] = {0x0};
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, crawl::header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, buffer1);
    //curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    //std::cout<<"head===>\n"<<cr.m_head_buf.size()<<" :\n"<<cr.m_head_buf<<std::endl;
    std::cout<<"head===>\n"<<buffer1<<std::endl;
    return buffer;
}
