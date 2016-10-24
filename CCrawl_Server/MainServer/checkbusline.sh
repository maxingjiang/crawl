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
LOG_NAME=/root/update_line.log #日志文件名

echo "${SYSDATE} start update_line now!" >> ${LOG_NAME}
/root/VenusCPP/tools/update_line >> ${LOG_NAME}

exit

