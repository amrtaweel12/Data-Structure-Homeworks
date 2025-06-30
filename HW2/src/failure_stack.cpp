#include "failure_stack.h"
void initialize_failed_stack(FAILURE_STACK *fs) {
    fs->top = -1;
}
bool isFull(FAILURE_STACK *fs) {
    return (fs->top + 1) == MAX_FAILED; 
}
bool isEmpty(FAILURE_STACK *fs) {
    return fs->top == -1;
}
void push(FAILURE_STACK *fs, PROCESS_QUEUE data) {
    if (!isFull(fs))
    {
        fs->top++;
        fs->stack[fs->top] = data;
        
        return;
    }
    printf("The stack is Full you can not add \n");
    
}
PROCESS_QUEUE pop(FAILURE_STACK *fs) {
    if (isEmpty(fs))
    {
        printf("Can not pop from Empty stack \n");
        exit(EXIT_FAILURE);
    }
    
    PROCESS_QUEUE popedQueue = fs->stack[fs->top];
    fs->top--;
    return popedQueue;
}