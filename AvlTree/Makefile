CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=avlTreeMain

all: $(PROGRAMS)

avlTreeMain: avlTreeMain.o avlTree.o
	$(CC) $(CFLAGS) -o $@ $^

avlTreeMain.o: avlTreeMain.c avlTree.h

avlTree.o: avlTree.c avlTree.h

clean:
	$(RM) *.o $(PROGRAMS)