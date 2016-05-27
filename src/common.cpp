/*
 * common.cpp
 *
 *  Created on: May 25, 2016
 *      Author: mxj
 */

#include "common.h"

log4cpp::Appender* logCPP::appender = new log4cpp::FileAppender("default", ".log");
log4cpp::PatternLayout* logCPP::pLayout = new log4cpp::PatternLayout();

void logCPP::info(char *file, int line, char *src)
{

	pLayout->setConversionPattern("%d: %p %c %x: %m%n");
	appender->setLayout(pLayout);

	log4cpp::Category& logger = log4cpp::Category::getInstance(std::string("log4cpp"));
	logger.setPriority(log4cpp::Priority::INFO);
	logger.addAppender(appender);
	char log[100] = {0x0};
	sprintf(log, "%s, %d, %s", file, line, src);
	logger.error(log);
}

void logCPP::debug(char *file, int line, char *src)
{

	pLayout->setConversionPattern("%d: %p %c %x: %m%n");
	appender->setLayout(pLayout);

	log4cpp::Category& logger = log4cpp::Category::getInstance(std::string("log4cpp"));
	logger.setPriority(log4cpp::Priority::INFO);
	logger.addAppender(appender);
	char log[100] = {0x0};
	sprintf(log, "%s, %d, %s", file, line, src);
	logger.debug(log);
}
void logCPP::warn(char *file, int line, char *src)
{

	pLayout->setConversionPattern("%d: %p %c %x: %m%n");
	appender->setLayout(pLayout);

	log4cpp::Category& logger = log4cpp::Category::getInstance(std::string("log4cpp"));
	logger.setPriority(log4cpp::Priority::INFO);
	logger.addAppender(appender);
	char log[100] = {0x0};
	sprintf(log, "%s, %d, %s", file, line, src);
	logger.warn(log);
}

void logCPP::error(char *file, int line, char *src)
{

	pLayout->setConversionPattern("%d: %p %c %x: %m%n");
	appender->setLayout(pLayout);

	log4cpp::Category& logger = log4cpp::Category::getInstance(std::string("log4cpp"));
	logger.setPriority(log4cpp::Priority::INFO);
	logger.addAppender(appender);
	char log[100] = {0x0};
	sprintf(log, "%s, %d, %s", file, line, src);
	logger.error(log);
}

