.SUFFIXES: .cpp .o
DIR_COMMON_PRO =          ./CommonServer
DIR_DB_PRO =          ./DBServer
DIR_THREADPOOL_PRO =      ./ThreadPoolServer
DIR_LOG_PRO =             ./LogServer
DIR_SOCKET_PRO =             ./SocketServer
DIR_CRAWL_PRO =           ./CrawlServer
DIR_CWEBPAGE_PRO =           ./CWebPageServer
DIR_GUMBO_PRO =           ./GumboServer
DIR_MAIN_PRO =             ./MainServer

#DIR_COMMON_PRO DIR_THREADPOOL_PRO DIR_LOG_PRO DIR_SOCKET_PRO DIR_CRAWL_PRO DIR_MAIN_PRO

all:DIR_COMMON_PRO DIR_DB_PRO DIR_THREADPOOL_PRO DIR_LOG_PRO DIR_SOCKET_PRO DIR_CRAWL_PRO DIR_GUMBO_PRO DIR_CWEBPAGE_PRO  DIR_MAIN_PRO

DIR_COMMON_PRO:
	cd ${DIR_COMMON_PRO}; make -f CommonServer.makefile

DIR_DB_PRO:
	cd ${DIR_DB_PRO}; make -f DBServer.makefile

DIR_THREADPOOL_PRO:
	cd ${DIR_THREADPOOL_PRO}; make -f ThreadPoolServer.makefile

DIR_LOG_PRO:
	cd ${DIR_LOG_PRO}; make -f LogServer.makefile

DIR_SOCKET_PRO:
	cd ${DIR_SOCKET_PRO}; make -f SocketServer.makefile

DIR_CRAWL_PRO:
	cd ${DIR_CRAWL_PRO}; make -f CrawlServer.makefile

DIR_CWEBPAGE_PRO:
	cd ${DIR_CWEBPAGE_PRO}; make -f CWebPageServer.makefile
	
DIR_GUMBO_PRO:
	cd ${DIR_GUMBO_PRO}; make -f GumboServer.makefile

DIR_MAIN_PRO:
	cd ${DIR_MAIN_PRO}; make

.PHONY:clean
clean:
	cd ${DIR_COMMON_PRO}; make -f CommonServer.makefile clean
	cd ${DIR_DB_PRO}; make -f DBServer.makefile clean
	cd ${DIR_THREADPOOL_PRO}; make -f ThreadPoolServer.makefile clean
	cd ${DIR_LOG_PRO}; make -f LogServer.makefile clean
	cd ${DIR_SOCKET_PRO}; make -f SocketServer.makefile clean
	cd ${DIR_CRAWL_PRO}; make -f CrawlServer.makefile clean
	cd ${DIR_CWEBPAGE_PRO}; make -f CWebPageServer.makefile clean
	cd ${DIR_GUMBO_PRO}; make -f GumboServer.makefile clean
	cd ${DIR_MAIN_PRO}; make clean
