/* Implements stack */

typedef struct stack * Stack;

// creates empty stack
Stack createStack(void);

// frees stack
void freeStack(Stack s);

// push to stack, returns pushed val
int push(Stack s, int val);

// pop from stack
// returns popped value, or null if stack is empty
int pop(Stack s);

// returns top of stack, without popping it
int peek(Stack s);

// returns if val is in stack
int search(Stack s, int val);

// get the size of stack
int getSize(Stack s);

// print stack
void printStack(Stack s);