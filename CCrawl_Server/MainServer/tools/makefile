.SUFFIXES: .cpp .o
DIR_INC = ../include
DIR_SRC = ./
DIR_OBJ = ./loadfile.o
MY_OBJ = ./
DIR_UBUNTU15_LIB = ./lib/ubuntu15lib/*
DIR_UBUNTU14_LIB = ./lib/ubuntu14lib/*
DIR_BIN = ./

SRC = $(wildcard ${DIR_SRC}/*.cpp)  
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = loadfile

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = g++
CFLAGS = -g -I${DIR_INC}

${BIN_TARGET}:${DIR_OBJ}
	$(CC) $(DIR_OBJ) -o $@ -lcurl -ljsoncpp -llog4cplus -lpthread -lzmq
    
${MY_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) $(CFLAGS) -c  $< -o $@
.PHONY:clean
clean:
	find ${MY_OBJ} -name *.o -exec rm -rf {} \;
	rm ${BIN_TARGET}
