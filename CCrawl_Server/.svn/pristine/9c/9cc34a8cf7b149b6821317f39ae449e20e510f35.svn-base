.SUFFIXES: .cpp .o
DIR_INC = ./include
DIR_3PARTY_INC = ./../3party/include
DIR_COMMON_INC = ./../lib/include/CommonServer
DIR_THREADPOOL_INC = ./../lib/include/ThreadPoolServer
SERVER_NAME = DBServer
DIR_SRC = ./src
DIR_OBJ = ./../obj/$(SERVER_NAME)
DIR_BIN = ./../lib

SRC = $(wildcard ${DIR_SRC}/*.cpp)  
#SRC += $(wildcard ${DIR_SRC}/requestHeaders/*.cpp)  
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = libDBServer.so

BIN_TARGET = ${DIR_BIN}/${TARGET}

INCLUDE_INC = -I${DIR_INC} -I${DIR_3PARTY_INC} -I${DIR_THREADPOOL_INC} -I${DIR_COMMON_INC} -I/usr/include/mysql/
CC = g++
CFLAGS = -g -c -ggdb -Wall -DBUILD_TIME="\"`date`\"" -DDEBUG
LIB = -lcurl -ljsoncpp -llog4cplus -lgumbo -lpthread -lzmq -lmysqlclient -lpthread

${BIN_TARGET}:${OBJ}
	$(CC) -shared $(OBJ) -o $@ $(LIB)
	mkdir -p ${DIR_BIN}/include/$(SERVER_NAME)/
	cp -r ${DIR_INC}/* ${DIR_BIN}/include/$(SERVER_NAME)/
    
${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	mkdir -p ${DIR_OBJ}
	$(CC) -fPIC $(CFLAGS) $(INCLUDE_INC) $< -o $@

.PHONY:clean
clean:
	find ${DIR_OBJ} -name "*.o" -exec rm -rf {} \;
	rm -rf ${DIR_BIN}/$(TARGET)
	rm -rf ${DIR_BIN}/include/$(SERVER_NAME)
