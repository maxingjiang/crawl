/*
 * common.cpp
 *
 *  Created on: May 25, 2016
 *      Author: mxj
 */

#include "common.h"

Logger ClogCPP::m_logger = Logger::getInstance(LOG4CPLUS_TEXT("log"));

void ClogCPP::init()
{
	log4cplus::initialize ();
	LogLog::getLogLog()->setInternalDebugging(false);
	try
	{
	     PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(LOG4CPLUSCONF));
	     LOG4CPLUS_INFO(m_logger, "begin logging....");
	 }
	 catch(...)
	 {
	     tcout << "Exception..." << endl;
	     LOG4CPLUS_FATAL(m_logger, "Exception occured...");
	 }
}
