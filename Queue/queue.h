/* Implements a queue */

typedef struct queue * Queue;

// creates empty queue
Queue createQueue();

// frees queue
void freeQueue(Queue q);

// enqueue (add to tail), returns its val
int enqueue(Queue q, int val);

// dequeue (pop from head), returns its val
int dequeue(Queue q);

// peeks at head of queue, without popping
int peek(Queue q);

// searches in queue
int search(Queue q, int val);

// get size of queue
int getSize(Queue q);

// print queue
void printQueue(Queue q);