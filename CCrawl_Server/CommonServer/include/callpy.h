/*
 * callpy.h
 *
 *  Created on: Aug 30, 2016
 *      Author: root
 */

#ifndef COMMONSERVER_INCLUDE_CALLPY_H_
#define COMMONSERVER_INCLUDE_CALLPY_H_

#include <iostream>
#include <Python.h>

using namespace std;

class CallPy
{
public:
	CallPy();
	~CallPy();
	int unicode2uft8(const string &desk, string &src);
};


#endif /* COMMONSERVER_INCLUDE_CALLPY_H_ */
