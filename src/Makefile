CC = gcc
OBJS = compression.o noeud.o decompression.o rle.o mtf.o compresseur.o
CFLAGS = -Wall
CPPFLAGS = -I$(HEADER)
EXEC = ../bin/compression
HEADER = ../header

all:	$(EXEC)

$(EXEC):	$(OBJS)
	$(CC) $(OBJS)  -o $(EXEC) -g


clean:
	rm $(OBJS) $(TEST)
