#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "queue.h"

struct queue {
    int size;               // size of queue
    struct node * tail;     // tail of queue
    struct node * list;     // list of nodes; list points to head of queue
};

struct node {
    int val;
    struct node * next;
};

// creates empty queue
Queue createQueue(){
    Queue q = malloc(sizeof(struct queue));
    q->size = 0;
    q->tail = 0;
    q->list = 0;
    return q;
}

// frees queue
void freeQueue(Queue q){
    // free the list
    struct node * curr = q->list;
    struct node * tmp;
    while(curr){
        tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    // free the queue
    free(q);
}

// enqueue (add to tail), returns its val
int enqueue(Queue q, int val){
    // create new node
    struct node * newNode = malloc(sizeof(struct node));
    newNode->val = val;
    newNode->next = 0;
    // is list currently empty?
    if(!q->list){
        // list is empty
        q->list = newNode;
        q->tail = newNode;
    } else {
        // list is not empty, update tail
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->size += 1;
    return newNode->val;
}

// dequeue (pop from head), returns its val
int dequeue(Queue q){
    assert(q->size);    // queue must not be empty
    struct node * popped = q->list;
    q->list = q->list->next;
    q->size -= 1;
    // free popped node and return
    int result = popped->val;
    free(popped);
    return result;
}

// peeks at head of queue, without popping
int peek(Queue q){
    assert(q->size);
    return q->list->val;
}

// searches in queue
int search(Queue q, int val){
    struct node * curr = q->list;
    while(curr){
        if(curr->val == val) return 1;
        curr = curr->next;
    }
    return 0;
}

// get size of queue
int getSize(Queue q){
    return q->size;
}

// print queue
void printQueue(Queue q){
    printf("Printing queue, from head to tail:");
    struct node * curr = q->list;
    while(curr){
        printf(" %d", curr->val);
        curr = curr->next;
    }
    printf("\n");
}