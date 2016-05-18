/*
 * test.h
 *
 *  Created on: May 17, 2016
 *      Author: mxj
 */

#ifndef INCLUDE_TEST_H_
#define INCLUDE_TEST_H_

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
#include <vector>
using namespace std;

int postUrl(char *filename);

int getCCT(char *Url);

int getUrl();

void setBusInfo();



#endif /* INCLUDE_TEST_H_ */
