.SUFFIXES: .cpp .o
DIR_INC = ./include
DIR_3PARTY_INC = ./../3party/include
DIR_COMMON_INC = ./../lib/include/ThreadPoolServer
DIR_SRC = ./src
DIR_OBJ = ./../obj/ThreadPoolServer
DIR_BIN = ./../lib

SRC += $(wildcard ${DIR_SRC}/../*.cpp)  
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = ThreadPoolServer

BIN_TARGET = ${TARGET}

INCLUDE_INC = -I${DIR_INC} -I${DIR_3PARTY_INC} -I${DIR_COMMON_INC} -I/usr/include/python2.7 -L/usr/lib64/python2.7/config
CC = g++
CFLAGS = -g -c -ggdb -Wall -DBUILD_TIME="\"`date`\"" -DDEBUG -std=c++11 -Wno-deprecated-declarations
LIB = ./../lib/*.so

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
