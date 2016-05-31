#ifndef INCLUDE_CRAWL_H_
#define INCLUDE_CRAWL_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <vector>

class Ccrawl
{
	public:
		std::vector<std::string> split(const  std::string& s, const std::string& delim);
		std::vector<std::string> split_response_cookie(std::string source, const  std::string& s);
		static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream); //libcurl callback
		static size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata); //libcurl callback
		void get_body(std::string search_src);


};

#endif /* INCLUDE_CRAWL_H_ */
