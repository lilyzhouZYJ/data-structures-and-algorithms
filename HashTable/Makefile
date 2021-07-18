CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=hashDemo

all: $(PROGRAMS)

hashDemo: hashDemo.o hash.o
	$(CC) $(CFLAGS) -o $@ $^
	valgrind -q --tool=memcheck --leak-check=yes ./hashDemo

hashDemo.o: hashDemo.c hash.h

hash.o: hash.c hash.h

clean:
	$(RM) *.o $(PROGRAMS)
