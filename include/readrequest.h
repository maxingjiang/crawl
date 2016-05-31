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

using namespace std;

class CreadConf
{
public:
	vector<string> readrequest(string &filename);
};

#endif /* INCLUDE_READREQUEST_H_ */
