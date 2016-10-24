/*
 * common.h
 *
 *  Created on: May 25, 2016
 *      Author: root
 */

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include <stdio.h>
#include <exception>

#define DIRBASE "/root/CCrawl_Server/"

#define LOG4CPLUSCONF DIRBASE "conf/log4cplus.properties"
#define PROXYCONF DIRBASE "conf/proxy.conf"
#define TESTPROXY DIRBASE "conf/testforproxy.conf"

#define DEFAULT_REQUEST_HEADERS DIRBASE "conf/requestHeadersConf/default.requestheaders"
#define WEIBO_REQUEST_HEADERS DIRBASE "conf/requestHeadersConf/weibo.requestheaders"
#define ZHIHU_REQUEST_HEADERS DIRBASE "conf/requestHeadersConf/zhihu.requestheaders"
#define DOUBAN_REQUEST_HEADERS DIRBASE "conf/requestHeadersConf/douban.requestheaders"

const int URL_LENGTH = 1024;

#define LOCATION_JUMP_NUMS 3

#define RESPONSESTATUSCODE "HTTP/"
#define RESPONSECONTENTTYPE "Content-Type:"
#define RESPONSELOCATION "Location:"
#define RESPONSESETCOOKIE "Set-Cookie:"

#define REQUEST_AcceptEncoding "Accept-Encoding: gzip, deflate, sdch, br"
#define REQUEST_AcceptLanguage "Accept-Language: zh-CN,zh;q=0.8"
#define REQUEST_Accept "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"
#define REQUEST_Cookie "Cookie:"
#define REQUEST_UserAgent "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.89 Safari/537.36"
#define REQUEST_Referer "Referer:"
#define REQUEST_CacheControl "Cache-Control:"
#define REQUEST_ContentLength "Content-Length:"
#define REQUEST_ContentType "Content-Type:"

enum request_mode
{
	GET,
	POST,
	POST_multipart
};


#define CRAWLDB_DB_CRAWLDB "crawldb"
#define CRAWLDB_HOST "127.0.0.1"
#define CRAWLDB_USER "root"
#define CRAWLDB_PWD "123456"
#define CRAWLDB_DB_SQL_LENGTH 1024

#define CRAWLDB_TABLE_headers "headers"
#define CRAWLDB_headers_ID "headersId"
#define CRAWLDB_headers_domain "domain"
#define CRAWLDB_headers_KEY "requestKey"
#define CRAWLDB_headers_VALUE "requestValue"

#define CRAWLDB_TABLE_PROXY "proxy"
#define CRAWLDB_PROXY_ID "proxyId"
#define CRAWLDB_PROXY_IP "proxyip"
#define CRAWLDB_PROXY_PORT "proxyport"

#define CRAWLDB_TABLE_cookies "cookies"
#define CRAWLDB_cookies_cookieid "cookieid"
#define CRAWLDB_cookies_website "website"
#define CRAWLDB_cookies_cookieKey "cookieKey"
#define CRAWLDB_cookies_cookieValue "cookieValue"
#define CRAWLDB_cookies_domain "domain"
#define CRAWLDB_cookies_path "path"
#define CRAWLDB_cookies_sendUseage "sendUseage"
#define CRAWLDB_cookies_isHttpOnly "isHttpOnly"
#define CRAWLDB_cookies_created "created"
#define CRAWLDB_cookies_deadline "deadline"

#endif /* INCLUDE_COMMON_H_ */
