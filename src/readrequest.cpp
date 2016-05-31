#include <iostream>
#include "readrequest.h"
using namespace std;


vector<string> CreadConf::readrequest(string &filename)
{
    const int LINE_LENGTH = 1024;
    char str[LINE_LENGTH]; 
    vector<string> headers;
    ifstream fin(filename.c_str());
    while( fin.getline(str,LINE_LENGTH) != NULL)
    {    
        //std::cout << "Read from file: " << str << std::endl;
    	headers.push_back(str);
    }
	return headers;
}

