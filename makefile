.SUFFIXES: .cpp .o
CC=g++
SERVERSRCS=save_http.cpp

SERVEROBJS=$(SERVERSRCS:.c=.o)
SERVEREXEC=save_http

all:$(SERVEROBJS) $(CLIENTOBJS)
	$(CC) -o $(SERVEREXEC) $(SERVEROBJS) -lcurl -g
	@echo '-------------ok--------------'

.c.o:
	$(CC) -o $@ -cpp $< 

clean:
	rm -f $(SERVEROBJS)
	rm -f core*


