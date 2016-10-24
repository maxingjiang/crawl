#!/bin/sh
#--------------------------------------------------------------------
# Fuction：检查xxx程序是否还在运行，不在则重启
# Author: 
# Created date:2016-06-06
# Definition：
#--------------------------------------------------------------------

USAGE="Usage: `basename $0`"
PROGRAM_NAME=$1
SYSDATE=`exec date +%Y%m%d%H%M%S`
LOGTIME=`exec date +%Y%m%d`
LOG_NAME=/root/crawl_server.log #日志文件名
status=$(ps -ef | grep crawl_server | grep -v grep | wc -l)
echo "status: " $status

if [ ${status} -eq 1 ]
then
	echo "${SYSDATE} crawl_server is running..." >> ${LOG_NAME}
elif  [ ${status} -eq 0 ]
then
	echo "$1 is faild!" >> ${LOG_NAME}
	echo "${SYSDATE} restart crawl_server now!" >> ${LOG_NAME}${LOGTIME}
	#/root/VenusCPP/build.sh start >> ${LOG_NAME}
fi	

exit

