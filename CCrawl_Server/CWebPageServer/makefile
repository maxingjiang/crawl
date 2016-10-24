.SUFFIXES: .cpp .o
DIR_INC = ./include
DIR_3PARTY_INC = ./../3party/include
DIR_COMMON_INC = ./../lib/include/CommonServer
DIR_THREADPOOL_INC = ./../lib/include/ThreadPoolServer
DIR_LOG_INC = ./../lib/include/LogServer
DIR_CRAWL_INC = ./../lib/include/CrawlServer
DIR_WEBPAGE_INC = ./../lib/include/CWebPageServer
DIR_DB_INC = ./../lib/include/DBServer
DIR_GUMBO_INC = ./../lib/include/GumboServer
SERVER_NAME = CWebPageServer
DIR_SRC = ./src
DIR_OBJ = ./../obj/$(SERVER_NAME)
DIR_BIN = ./../lib

SRC += $(wildcard ${DIR_SRC}/../*.cpp)  
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = CWebPageServer

BIN_TARGET = ${TARGET}

INCLUDE_INC = -I${DIR_INC} -I${DIR_3PARTY_INC} -I${DIR_THREADPOOL_INC} -I${DIR_LOG_INC} -I${DIR_COMMON_INC} -I${DIR_CRAWL_INC} -I${DIR_WEBPAGE_INC} -I${DIR_DB_INC} -I${DIR_GUMBO_INC} -I/usr/include/mysql/
CC = g++
CFLAGS = -g -c -ggdb -Wall -DBUILD_TIME="\"`date`\"" -DDEBUG -std=c++11 -Wno-deprecated-declarations
LIB = -lcurl -ljsoncpp -llog4cplus -lgumbo -lpthread -lzmq -lmysqlclient -lpthread ./../lib/*.so

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ) -o $@ $(LIB)

${DIR_OBJ}/%.o:${DIR_SRC}/../%.cpp
	mkdir -p ${DIR_OBJ}
	$(CC) $(CFLAGS) $(INCLUDE_INC) $< -o $@

.PHONY:clean
clean:
	find ${DIR_OBJ} -name "*.o" -exec rm -rf {} \;
	rm $(BIN_TARGET)
	rm -rf ${DIR_BIN}/include/$(SERVER_NAME)
