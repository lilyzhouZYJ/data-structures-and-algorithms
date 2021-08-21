CC=c99
CFLAGS=-g3 -Wall

PROGRAMS=queueDemo

all: $(PROGRAMS)

queueDemo: queueDemo.o queue.o
	$(CC) $(CFLAGS) -o $@ $^
	valgrind -q --tool=memcheck --leak-check=yes ./queueDemo

queueDemo.o: queueDemo.c queue.h

queue.o: queue.c queue.h

clean:
	$(RM) *.o $(PROGRAMS)