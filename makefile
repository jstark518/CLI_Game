CC = gcc
LIBS = -lncurses
CFLAGS = -Wall -g $(LIBS)
EXE = main
OBJS = *.o
SRCS = *.c

all: compile
	$(CC) $(LIBS) -o $(EXE) $(OBJS)
	
compile: 
	$(CC) $(CLFAGS) -c $(SRCS)

clean:
	rm -f $(EXE) $(OBJS)
