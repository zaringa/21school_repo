#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL 1

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

int init(Stack *stack, int capacity);
int push(Stack *stack, int value);
int pop(Stack *stack, int *value);
void destroy(Stack *stack);

#endif