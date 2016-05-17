#include <iostream>
#include <fstream>
#include "readrequest.h"
using namespace std;

readConf::readConf(std::string filename)
{
	m_requestconf.clear();
	m_filename = filename;
}

readConf::~readConf()
{
	m_requestconf.clear();
	m_filename = "";
}

void readConf::readrequest()
{
    const int LINE_LENGTH = 2048; 
    char str[LINE_LENGTH]; 
    ifstream fin(m_filename.c_str()); 
    while( fin.getline(str,LINE_LENGTH) != NULL)
    {    
        std::cout << "Read from file: " << str << std::endl;
	m_requestconf.push_back(str);
    }
	
}

