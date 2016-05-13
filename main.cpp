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

int main(int argc, char *argv[])
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
		headers = curl_slist_append(headers, (*iter).c_str());
	}

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    //curl_easy_setopt(curl, CURLOPT_URL, "http://www.douguo.com/cookbook/1360495.html");  
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.douguo.com");  
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, crawl::write_data);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, crawl::header_callback);
    //curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_perform(curl);
    cr.get_body(curl);
    curl_easy_cleanup(curl);
    std::cout<<"head===>\n"<<cr.m_head_buf.size()<<": "<<cr.m_head_buf<<std::endl;
    exit(0);
}
