/*
 * common.h
 *
 *  Created on: May 25, 2016
 *      Author: mxj
 */

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include <stdio.h>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>

#define BUSLINECONF "/root/VenusCPP/conf/busline.conf"
#define COOKIECONF "/root/VenusCPP/conf/cookie.conf"
#define LOG4CPLUSCONF "/root/VenusCPP/conf/log4cplus.properties"
#define PROXYCONF "/root/VenusCPP/conf/proxy.conf"
#define REQUESTCONF "/root/VenusCPP/conf/request.conf"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

class ClogCPP
{
public:
	static Logger m_logger;
	static void init();
};

#endif /* INCLUDE_COMMON_H_ */
