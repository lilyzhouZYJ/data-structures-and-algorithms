#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "queue.h"

int main(int argc, char ** argv){

    // create queue
    Queue q = createQueue();

    // enqueue some values
    printf("Enqueue %d\n", enqueue(q, 1));
    printf("Enqueue %d\n", enqueue(q, 2));
    printf("Enqueue %d\n", enqueue(q, 3));
    printf("Enqueue %d\n", enqueue(q, 4));
    printf("Enqueue %d\n", enqueue(q, 5));
    printf("Enqueue %d\n", enqueue(q, 6));

    // search for some values
    printf("Is %d in the queue? %d\n", 5, search(q, 5));
    printf("Is %d in the queue? %d\n", 8, search(q, 8));

    // get the size of queue
    printf("Queue size is %d\n", getSize(q));
    
    // print queue
    printQueue(q);

    // peak at some values
    printf("Peeking at %d\n", peek(q));

    // dequeue some values
    printf("Dequeue %d\n", dequeue(q));
    printf("Dequeue %d\n", dequeue(q));
    printf("Dequeue %d\n", dequeue(q));

    // get the size again
    printf("Queue size is %d\n", getSize(q));

    // search for some values again
    printf("Is %d in the queue? %d\n", 5, search(q, 5));
    printf("Is %d in the queue? %d\n", 3, search(q, 3));

    // print queue
    printQueue(q);

    // free queue
    freeQueue(q);

    return 0;
}