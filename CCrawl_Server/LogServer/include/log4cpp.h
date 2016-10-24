/*
 * log4cpp.h
 *
 *  Created on: May 25, 2016
 *      Author: root
 */

#ifndef INCLUDE_LOG4CPP_H_
#define INCLUDE_LOG4CPP_H_

#include <stdio.h>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

class ClogCPP
{
public:
	static Logger m_logger;
	static void init();
};

#endif /* INCLUDE_LOG4CPP_H_ */
