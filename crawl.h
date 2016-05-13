#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include <vector>

class crawl
{
	public:

		std::vector<std::string> split(const  std::string& s, const std::string& delim);
		static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);
		static size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata);
		void get_body(CURL *curl);
	public:
		static std::string m_data_buf;
		static int m_data_shift;
		static std::string m_head_buf;
		static int m_head_shift;
	private:

};
