CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=stackDemo

all: $(PROGRAMS)

stackDemo: stackDemo.o stack.o
	$(CC) $(CFLAGS) -o $@ $^
	valgrind -q --tool=memcheck --leak-check=yes ./stackDemo

stackDemo.o: stackDemo.c stack.h

stack.o: stack.c stack.h

clean:
	$(RM) *.o $(PROGRAMS)