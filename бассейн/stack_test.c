#include "stack.h"

#include <stdio.h>

void run_tests() {
    Stack stack;
    int result;
    int value;

    result = init(&stack, 5);
    if (result == FAIL) {
        printf("Test Init: FAIL\n");
        return;
    } else {
        printf("Test Init: SUCCESS\n");
    }

    result = push(&stack, 10);
    if (result == FAIL) {
        printf("Test Push: FAIL\n");
        return;
    } else {
        printf("Test Push: SUCCESS\n");
    }

    result = pop(&stack, &value);
    if (result == FAIL || value != 10) {
        printf("Test Pop: FAIL\n");
        return;
    } else {
        printf("Test Pop: SUCCESS\n");
    }

    destroy(&stack);
}

int main() {
    run_tests();
    return 0;
}
