#ifndef INCLUDE_READREQUEST_H_
#define INCLUDE_READREQUEST_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>

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

#endif /* INCLUDE_READREQUEST_H_ */
