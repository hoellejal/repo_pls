CC = gcc
OBJS = compression.o noeud.o
TEST = ../test/test_compression.o
CFLAGS = -Wall
CPPFLAGS = -I$(HEADER)
EXEC = ../bin/compression
HEADER = ../header

all:	$(EXEC)

$(EXEC):	$(OBJS) $(TEST)
	$(CC) $(OBJS) $(TEST) -o $(EXEC)


clean:
	rm $(OBJS) $(TEST)
