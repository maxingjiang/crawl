#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <vector>

class readConf
{
	public:
		readConf(std::string filename);
		~readConf();
		void readrequest();
	public:
		std::vector<std::string> m_requestconf;
		std::string m_filename;
};
