/*
 * CPPregex.h
 *
 *  Created on: Aug 2, 2016
 *      Author: root
 */

#ifndef COMMONSERVER_INCLUDE_CPPREGEX_H_
#define COMMONSERVER_INCLUDE_CPPREGEX_H_

#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

class CPPregex
{
public:
	int getCharset(const string &responseBody, string &charset, const string &charsetRegex = "<meta.*?charset=['\"]?(.*?)['\"]");
	void removeSpace(string &src); //clear tab ,\r,\n

};

#endif /* COMMONSERVER_INCLUDE_CPPREGEX_H_ */
