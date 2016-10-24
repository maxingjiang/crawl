.SUFFIXES: .cpp .o
DIR_INC = ./include
DIR_3PARTY_INC = ./../3party/include
DIR_COMMON_INC = ./../lib/include/CommonServer
DIR_THREADPOOL_INC = ./../lib/include/ThreadPoolServer
DIR_CRAWL_INC = ./../lib/include/CrawlServer
DIR_LOG_INC = ./../lib/include/LogServer
DIR_DB_INC = ./../lib/include/DBServer
DIR_GUMBO_INC = ./../lib/include/GumboServer
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./

SRC = $(wildcard ${DIR_SRC}/*.cpp)  
#SRC += $(wildcard ${DIR_SRC}/requestHeaders/*.cpp)  
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = MainServer

BIN_TARGET = ${DIR_BIN}/${TARGET}

INCLUDE_INC = -I${DIR_INC} -I${DIR_3PARTY_INC} -I${DIR_THREADPOOL_INC} -I${DIR_COMMON_INC} \
-I${DIR_CRAWL_INC} -I${DIR_LOG_INC} -I${DIR_DB_INC} -I${DIR_GUMBO_INC} -I/usr/include/mysql/
CC = g++
CFLAGS = -g -c -ggdb -Wall -DBUILD_TIME="\"`date`\"" -DDEBUG -std=c++11 -Wno-deprecated-declarations
LIB = -lcurl -ljsoncpp -llog4cplus -lpthread -lgumbo -lzmq ./../lib/*.so

all:${BIN_TARGET} ${OBJ}

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ) -o $@ $(LIB)
    
${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	mkdir -p ${DIR_OBJ}
	$(CC) $(CFLAGS) $(INCLUDE_INC) $< -o $@

.PHONY:clean
clean:
	find ${DIR_OBJ} -name "*.o" -exec rm -rf {} \;
	rm -rf ${DIR_BIN}/$(TARGET)
