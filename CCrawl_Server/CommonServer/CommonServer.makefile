.SUFFIXES: .cpp .o
DIR_INC = ./include
DIR_3PARTY_INC = ./../3party/include
DIR_COMMON_INC = ./../lib/include/CommonServer
DIR_THREADPOOL_INC = ./../lib/include/ThreadPoolServer
DIR_SRC = ./src
DIR_OBJ = ./../obj/CommonServer
DIR_BIN = ./../lib

SRC = $(wildcard ${DIR_SRC}/*.cpp)  
#SRC += $(wildcard ${DIR_SRC}/requestHeaders/*.cpp)  
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = libCommonServer.so

BIN_TARGET = ${DIR_BIN}/${TARGET}

INCLUDE_INC = -I${DIR_INC} -I${DIR_3PARTY_INC} -I${DIR_THREADPOOL_INC} -I${DIR_COMMON_INC} -I/usr/include/python2.7 -L/usr/lib64/python2.7/config
CC = g++
CFLAGS = -g -c -ggdb -Wall -DBUILD_TIME="\"`date`\"" -DDEBUG -std=c++11 -Wno-deprecated-declarations
LIB = -lcurl -ljsoncpp -llog4cplus -lgumbo -lpthread -lzmq  -lboost_regex -lpython2.7

${BIN_TARGET}:${OBJ}
	$(CC) -shared $(OBJ) -o $@ $(LIB)
	mkdir -p ${DIR_BIN}/include/CommonServer/
	cp -r ${DIR_INC}/* ${DIR_BIN}/include/CommonServer/
	cp -r ${DIR_SRC}/*.py ${DIR_BIN}/
    
${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	mkdir -p ${DIR_OBJ}
	$(CC) -fPIC $(CFLAGS) $(INCLUDE_INC) $< -o $@

.PHONY:clean
clean:
	find ${DIR_OBJ} -name "*.o" -exec rm -rf {} \;
	rm -rf ${DIR_BIN}/$(TARGET)
	rm -rf ${DIR_BIN}/include/CommonServer
