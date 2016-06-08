.SUFFIXES: .cpp .o
DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_UBUNTU15_LIB = ./lib/ubuntu15lib/*
DIR_UBUNTU14_LIB = ./lib/ubuntu14lib/*
DIR_BIN = ./

SRC = $(wildcard ${DIR_SRC}/*.cpp)  
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = crawl_server

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = g++
CFLAGS = -g -I${DIR_INC}

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ)  -o $@ -lcurl -ljsoncpp -llog4cplus -lzmq -lpthread
    
${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) $(CFLAGS) -c  $< -o $@
.PHONY:clean
clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
