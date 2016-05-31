#!/bin/bash

if [[ $# != 1 ]];then
	echo "Usage: $0 [check|start|stop]"
	exit -1;
fi
if [[ $1 == "check" ]];then
	./configure	

elif [[ $1 == "start" ]];then
	echo 'Server is running, listening on port 7766....'
	./crawl_server &
	ps > .pidfile
elif [[ $1 == "stop" ]];then
	pid=`cat .pidfile | grep "crawl_server" | awk '{print $1}'`
	kill -9 $pid
	echo "stop the crawl_server"
fi
