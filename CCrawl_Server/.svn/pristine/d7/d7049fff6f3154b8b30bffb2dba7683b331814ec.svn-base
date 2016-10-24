/*
 * split.h
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#ifndef INCLUDE_SPLIT_H_
#define INCLUDE_SPLIT_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

namespace namespace_split
{
	size_t write_data(char *data, size_t size, size_t nmemb, string *writerData); //libcurl callback
	size_t write_header(char *data, size_t size, size_t nmemb, string *writerData); //libcurl callback

	size_t fwrite_data(void *data, size_t size, size_t nmemb, void *stream); //write image to file
}

class Csplit
{
public:
	vector<string> split(const string& source, const string& s);

};

struct FtpFile
{
  const char *filename;
  FILE *stream;
};

#endif /* INCLUDE_SPLIT_H_ */
