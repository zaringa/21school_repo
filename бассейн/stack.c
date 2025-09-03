#include "stack.h"

int init(Stack *stack, int capacity) {
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (int *)malloc(capacity * sizeof(int));
    if (!stack->data) {
        return FAIL;
    }
    return SUCCESS;
}

int push(Stack *stack, int value) {
    if (stack->top >= stack->capacity - 1) {
        return FAIL;
    }
    stack->data[++stack->top] = value;
    return SUCCESS;
}

int pop(Stack *stack, int *value) {
    if (stack->top < 0) {
        return FAIL;
    }
    *value = stack->data[stack->top--];
    return SUCCESS;
}

void destroy(Stack *stack) {
    free(stack->data);
    stack->data = NULL;
    stack->top = -1;
    stack->capacity = 0;
}
