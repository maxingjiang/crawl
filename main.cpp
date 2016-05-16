#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include "readrequest.h"
#include "crawl.h"
#include <vector>
using namespace std;

int postUrl(char *filename)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL)
        return 0;
    curl = curl_easy_init();
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"cuisineBookId\":\"100\"}");
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.88.128:8083/api/user/getcuisine");
     curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return 1;
}

int getUrl()
{
    CURL *curl;
 
    curl_global_init(CURL_GLOBAL_ALL);  
    curl=curl_easy_init();
    struct curl_slist *headers = NULL;
	std::string filename = "request.conf";
	readConf rd(filename);
	crawl cr;
	rd.readrequest();
	std::vector<std::string>::iterator iter = rd.m_requestconf.begin();
	for(; iter != rd.m_requestconf.end(); iter++)
	{
		cout<<*iter<<endl;
		headers = curl_slist_append(headers, (*iter).c_str());
	}

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, "http://cp2.douguo.net/upload/caiku/f/7/7/yuan_f7c4345c3ae8c8eeabfdef07e974c897.jpg");  
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    //curl_easy_setopt(curl, CURLOPT_URL, "http://www.douguo.com");  
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, crawl::write_data);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, crawl::header_callback);
    //curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_perform(curl);
    cr.get_body(curl);
    curl_easy_cleanup(curl);
    std::cout<<"head===>\n"<<cr.m_head_buf.size()<<": "<<cr.m_head_buf<<std::endl;
    exit(0);
}

int main(int argc, char *argv[])
{
    getUrl();
    char file[] = "post.html";
    postUrl(file);    
}
