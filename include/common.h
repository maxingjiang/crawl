/*
 * common.h
 *
 *  Created on: May 25, 2016
 *      Author: mxj
 */

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include <stdio.h>
#include "log4cpp/Portability.hh"
#ifdef LOG4CPP_HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <iostream>
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#ifdef LOG4CPP_HAVE_SYSLOG
#endif
#include "log4cpp/Layout.hh"
#include <log4cpp/PatternLayout.hh>
#include "log4cpp/Priority.hh"

class logCPP
{
public:
	static log4cpp::Appender* appender;
	static log4cpp::PatternLayout* pLayout;
	static void info(char *file, int line, char *src);
	static void debug(char *file, int line, char *src);
	static void warn(char *file, int line, char *src);
	static void error(char *file, int line, char *src);
};

#endif /* INCLUDE_COMMON_H_ */
