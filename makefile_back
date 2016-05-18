.SUFFIXES: .cpp .o
CC=g++
BUILD=$(shell pwd)/bin
SERVERSRCS=crawl.cpp \
		readrequest.cpp \
		main.cpp

SERVEROBJS=$(SERVERSRCS:.cpp=.o)
SERVEREXEC=crawl

all:$(SERVEROBJS)
	$(CC) -o $(SERVEREXEC) $(SERVEROBJS) -lcurl -g
	@echo '-------------ok--------------'

.c.o:
	$(CC) -c -g $< -o $(BUILD)/$@

clean:
	rm -f $(SERVEROBJS)
	rm -f core*


