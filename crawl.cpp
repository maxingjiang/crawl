#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include <vector>
 
std::string res_buf;
int shift;
std::string head_buf;
int head_shift;

std::vector<std::string> split(const  std::string& s, const std::string& delim)  
{  
    std::vector<std::string> elems;  
    size_t pos = 0;  
    size_t len = s.length();  
    size_t delim_len = delim.length();  
    if (delim_len == 0) 
        return elems;  
    while (pos < len)  
    {  
        int find_pos = s.find(delim, pos);  
        if (find_pos < 0)  
        {  
            elems.push_back(s.substr(pos, len - pos));  
            break;  
        }  
        elems.push_back(s.substr(pos, find_pos - pos));  
        pos = find_pos + delim_len;  
    }  
    return elems;  
}
  
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)  
{
    //printf("============\n===========%s\n", (char *)ptr);
    int res_size = size * nmemb;
    res_buf = res_buf + (char *)ptr;
    shift += res_size;
    return size * nmemb;
}
 
size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    int res_size = size * nitems;
    head_buf = head_buf + buffer;
    head_shift += res_size;
    return size * nitems;   
}

void get_body(CURL *curl)
{
    std::string str2 = "http://www.douguo.com";
    std::size_t found = res_buf.find(str2);
    if (found!=std::string::npos)
        std::cout << "first found at: " << found << '\n';
    
    std::vector<std::string> ret = split(res_buf, "\n");
    std::vector<std::string>::iterator iter = ret.begin();
    for(;iter != ret.end(); iter++)
    {
	int findpos = (*iter).find(str2, 0);
	if(findpos >= 0)
	    std::cout<<*iter<<std::endl;
    }
}

int main(int argc, char *argv[])
{
    CURL *curl;
 
    curl_global_init(CURL_GLOBAL_ALL);  
    curl=curl_easy_init();
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: Agent-007");
    headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.8.1.11) Gecko/20071127 Firefox/2.0.0.11");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    //curl_easy_setopt(curl, CURLOPT_URL, "http://www.douguo.com/cookbook/1360495.html");  
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.douguo.com");  
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    //curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_perform(curl);
    //get_body(curl);
    curl_easy_cleanup(curl);
    std::cout<<"head===>\n"<<head_buf.size()<<": "<<head_buf<<std::endl;
    exit(0);
}
