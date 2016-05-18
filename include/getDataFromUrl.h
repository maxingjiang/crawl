
#ifndef INCLUDE_GETDATAFROMURL_H_
#define INCLUDE_GETDATAFROMURL_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include "readrequest.h"
#include "crawl.h"
#include <curl/curl.h>
#include <curl/easy.h>

using namespace :: std;
using std::string;

string getBusInfoByUrl(CURL *curl, string &Url);

#endif /* INCLUDE_GETDATAFROMURL_H_ */
