#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "stack.h"

struct stack {
    int size;               // size of stack
    struct node * list;     // list of stack elements
};

struct node {
    int val;
    struct node * next;
};

// creates empty stack
Stack createStack(void){
    Stack s = malloc(sizeof(struct stack));
    s->size = 0;
    s->list = 0;
    return s;
}

// frees stack
void freeStack(Stack s){
    // frees linked list
    struct node * curr = s->list;
    while(curr){
        struct node * tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    // frees stack
    free(s);
}

// push to stack, returns pushed val
int push(Stack s, int val){
    // create new node
    struct node * newNode = malloc(sizeof(struct node));
    newNode->val = val;
    newNode->next = s->list;
    // append to s->list
    s->list = newNode;
    s->size += 1;
    // return
    return newNode->val;
}

// pop from stack
// returns popped value, or null if stack is empty
int pop(Stack s){
    struct node * popped = s->list;
    // remove popped node
    s->size -= 1;
    s->list = s->list->next;
    // free popped and return
    int result = popped->val;
    free(popped);
    return result;
}

// returns top of stack, without popping it
int peek(Stack s){
    return s->list->val;
}

// returns if val is in stack
int search(Stack s, int val){
    struct node * curr = s->list;
    while(curr){
        if(curr->val == val) return 1;
        curr = curr->next;
    }
    return 0;
}

// get the size of stack
int getSize(Stack s){
    return s->size;
}

// print stack
void printStack(Stack s){
    printf("Stack, starting from the top:");
    struct node * curr = s->list;
    while(curr){
        printf(" %d", curr->val);
        curr = curr->next;
    }
    printf("\n");
}