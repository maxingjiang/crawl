.SUFFIXES: .cpp .o

CC=g++
SERVERSRCS=server.cpp\
	   client.cpp
CLIENTSRCS=client.cpp
SERVEROBJS=server.o
CLIENTOBJS=client.o
SERVEREXEC=server
CLIENTEXEC=client

all:$(SERVEROBJS) $(CLIENTOBJS)
	$(CC) -o $(SERVEREXEC) $(SERVEROBJS) ./libboost_system.so.1.57.0 ./libboost_thread.so.1.57.0
	$(CC) -o $(CLIENTEXEC) $(CLIENTOBJS) ./libboost_system.so.1.57.0 ./libboost_thread.so.1.57.0 -lpthread
	@echo '-------------ok--------------'

.c.o:
	$(CC) -g -o $@ -c $< 

clean:
	rm -f $(SERVEROBJS)
	rm -f $(SERVEREXEC)
	rm -f $(CLIENTOBJS)
	rm -f $(CLIENTEXEC)
	rm -f core*


