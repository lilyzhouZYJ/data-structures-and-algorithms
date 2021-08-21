#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "stack.h"

int main(int argc, char ** argv){

    // create stack
    Stack s = createStack();

    // push some values to stack
    printf("Pushing %d\n", push(s, 1));
    printf("Pushing %d\n", push(s, 2));
    printf("Pushing %d\n", push(s, 3));
    printf("Pushing %d\n", push(s, 4));
    printf("Pushing %d\n", push(s, 5));
    printf("Pushing %d\n", push(s, 6));

    // search for some values
    printf("Is %d in the stack? %d\n", 5, search(s, 5));
    printf("Is %d in the stack? %d\n", 8, search(s, 8));

    // get the size of stack
    printf("Stack size is %d\n", getSize(s));
    
    // print stack
    printStack(s);

    // peak at some values
    printf("Peeking at %d\n", peek(s));

    // pop some values
    printf("Popping %d\n", pop(s));
    printf("Popping %d\n", pop(s));
    printf("Popping %d\n", pop(s));

    // get the size again
    printf("Stack size is %d\n", getSize(s));

    // search for some values again
    printf("Is %d in the stack? %d\n", 5, search(s, 5));
    printf("Is %d in the stack? %d\n", 3, search(s, 3));

    // print stack
    printStack(s);

    // free stack
    freeStack(s);

    return 0;
}