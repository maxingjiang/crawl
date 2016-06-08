.SUFFIXES: .cpp .o

CC=g++
#SERVERSRCS=server.cpp
CLIENTSRCS=client.cpp
#SERVEROBJS=server.o
CLIENTOBJS=client.o
#SERVEREXEC=server
CLIENTEXEC=client

DIR_UBUNTU15_LIB = ../lib/ubuntu15lib/*
DIR_UBUNTU14_LIB = ../lib/ubuntu14lib/*

all:$(SERVEROBJS) $(CLIENTOBJS)
	#$(CC) -o $(SERVEREXEC) $(SERVEROBJS) -lzmq
	$(CC) -o $(CLIENTEXEC) $(CLIENTOBJS) -lzmq
	@echo '-------------ok--------------'

.c.o:
	$(CC) -g -o $@ -c $< 

clean:
	rm -f $(SERVEROBJS)
	rm -f $(SERVEREXEC)
	rm -f $(CLIENTOBJS)
	rm -f $(CLIENTEXEC)
	rm -f core*


