#include <iostream>
#include "crawl.h"
 
std::string crawl::m_data_buf = "";
int crawl::m_data_shift = 0;
std::string crawl::m_head_buf = "";
int crawl::m_head_shift = 0;

std::vector<std::string> crawl::split(const  std::string& s, const std::string& delim)  
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
  
size_t crawl::write_data(void *ptr, size_t size, size_t nmemb, void *stream)  
{
    //printf("============\n===========%s\n", (char *)ptr);
    int res_size = size * nmemb;
    m_data_buf = m_data_buf + (char *)ptr;
    m_data_shift += res_size;
    return size * nmemb;
}
 
size_t crawl::header_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    int res_size = size * nitems;
    m_head_buf = m_head_buf + buffer;
    m_head_shift += res_size;
    return size * nitems;   
}

void crawl::get_body(CURL *curl)
{
    std::string str2 = "http://www.douguo.com";
    std::size_t found = m_data_buf.find(str2);
    if (found!=std::string::npos)
        std::cout << "first found at: " << found << '\n';
    
    std::vector<std::string> ret = split(m_data_buf, "\n");
    std::vector<std::string>::iterator iter = ret.begin();
    for(;iter != ret.end(); iter++)
    {
	int findpos = (*iter).find(str2, 0);
	if(findpos >= 0)
	    std::cout<<*iter<<std::endl;
    }
}

