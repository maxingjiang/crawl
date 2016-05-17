#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include "readrequest.h"
#include "crawl.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <vector>
using namespace std;

int postUrl(char *filename)
{
    std:;cout<<"post===>\n";
    CURL *curl;
    CURLcode res;
    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL)
        return 0;
    curl = curl_easy_init();
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_POST, 1L);
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"cuisineBookId\":\"100\"}");
        //curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.199.128:8080/api/user/getcuisine");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"userid\":\"101\",\"tel\":\"18612304173\",\"password\":\"123456a\"}");
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.199.128:8080/api/user/login");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return 1;
}

int getCCT(char *Url)
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
        curl_easy_setopt(curl, CURLOPT_URL, Url);
        //curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, crawl::header_callback);
	    //curl_easy_setopt(curl, CURLOPT_HEADERDATA, fp);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        std::cout<<"head===>\n"<<crawl::m_head_buf.size()<<" :\n"<<crawl::m_head_buf<<std::endl;
        std::vector<std::string> iter_cookie = cr.split_response_cookie("Set-Cookie:");
        std::vector<std::string>::iterator iter = iter_cookie.begin();
        FILE *pcookie;
        if ((pcookie = fopen("cookie.conf", "w")) == NULL)
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

int getUrl()
{
    CURL *curl;
    crawl cr;
    cr.clear();
    curl_global_init(CURL_GLOBAL_ALL);  
    curl=curl_easy_init();
    struct curl_slist *headers = NULL;
    std::string filename = "request.conf";
    readConf rd(filename);
    rd.readrequest();
    std::vector<std::string>::iterator iter = rd.m_requestconf.begin();
    cout<<"request header===>: \n";
    for(; iter != rd.m_requestconf.end(); iter++)
    {
        cout<<*iter<<endl;
        //headers = curl_slist_append(headers, (*iter).c_str());
    }

    filename = "cookie.conf";
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

int main(int argc, char *argv[])
{
    //getUrl();
    //char url[] = "http://220.197.219.150:9083/admin/login?userName=yang&password=123456";
    char url[] = "http://220.197.219.150:9083/admin/login?userName=yang&password=123456";
    //postUrl(file);
    //getCCT(url);
    getUrl();
    exit(0);
}
