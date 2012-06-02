# Server With Threads Makefile

CC=gcc
UNAME=$(shell uname)

#CFLAGS= -Wall -g -O2 $(INCLUDE)                                                           
LDFLAGS=                                                                        

#Linux
ifeq ($(UNAME),Linux)
INCLUDE= -I./ $(KERNEL_HEADERS) 
endif

#MAC OS X
ifeq ($(UNAME),Darwin)
INCLUDE= -I./ $(KERNEL_HEADERS) -I/opt/local/include 
endif

#Linux
ifeq ($(UNAME),Linux)
LIBS= -lpthread 
endif

#MAC OS X
ifeq ($(UNAME),Darwin)
LIBS= -lpthread 
endif
LOADLIBES= $(LIBS)

OBJS= server-with-threads.o client_manager.o server.o 

CFLAGS= -g -D_PC_ $(INCLUDE) -Wall

EXEC= server-with-threads

#default: libbridge all
default: all

all: $(OBJS) $(EXEC)

$(EXEC): $(OBJS)

clean:
	-rm -f $(OBJS)
	-rm -f $(EXEC)
	

rebuild: clean all

