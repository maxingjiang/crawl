.SUFFIXES: .cpp .o
DIR_3PARTY_INC = ./../3party/include
DIR_THREADPOOL_INC = ./../lib/include/SocketServer
SERVER_NAME = client
DIR_SRC = .
DIR_OBJ = .
DIR_BIN = .

SRC += $(wildcard ${DIR_SRC}/${SERVER_NAME}.cpp)  
OBJ = $(patsubst ${SERVER_NAME}.cpp,${DIR_OBJ}/${SERVER_NAME}.o,$(notdir ${SRC})) 

TARGET = client

BIN_TARGET = ${TARGET}

INCLUDE_INC = -I${DIR_3PARTY_INC} -I${DIR_THREADPOOL_INC} -I${DIR_LOG_INC} -I${DIR_COMMON_INC} -I${DIR_CRAWL_INC} -I${DIR_DB_INC} -I${DIR_Bus_INC} -I/usr/include/mysql/
CC = g++
CFLAGS = -g -c -ggdb -Wall -DBUILD_TIME="\"`date`\"" -DDEBUG -std=c++11
LIB = -lpthread -lzmq -lpthread ./../lib/*.so

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ) -o $@ $(LIB)

${DIR_OBJ}/${SERVER_NAME}.o:${DIR_SRC}/${SERVER_NAME}.cpp
	mkdir -p ${DIR_OBJ}
	$(CC) $(CFLAGS) $(INCLUDE_INC) $< -o $@

.PHONY:clean
clean:
	find ${DIR_OBJ} -name "$(SERVER_NAME).o" -exec rm -rf {} \;
	rm  -rf $(BIN_TARGET)
