#!/bin/bash

if [[ $# != 1 ]];then
	echo "Usage: $0 [check]"
	exit -1;
fi
if [[ $1 == "check" ]];then
	msql=`which mysqld`
	if [[ "${msql}x" == "x" ]];then
		echo "mysqld not found,now installing mysql-server......"
		echo "mysql-server mysql-server/root_password password 123456" | /usr/bin/debconf-set-selections
		echo "mysql-server mysql-server/root_password_again password 123456" | /usr/bin/debconf-set-selections
		apt-get install mysql-server -y
	fi
	/etc/init.d/mysql restart && \
        mysql -uroot -p123456 -e"CREATE DATABASE \`crawldb\` character set utf8;" && \
        mysql -uroot -p123456 crawldb < ./crawldb.sql  &>> .log
fi	

