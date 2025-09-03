#include <stdio.h>
#include <stdlib.h>
#define O NULL
#define MAX_SIZE 100

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = *a;
}
int *adin1(int x, int y) {
    int *a;
    a = malloc(MAX_SIZE * MAX_SIZE * sizeof(int));
    return a;
}
int **adin2(int x, int y) {
    int **a = O;
    a = malloc(x * sizeof(int *) + x * y * sizeof(int));
    if (a == O) return O;
    for (int i = 0; i < x; i++) {
        if (a[i] == O) {
            for (int j = 0; j < i; j++) free(a[j]);
            free(a);
            return O;
        }
    }
    return a;
}
int **adin3(int x, int y) {
    int **a = O;
    a = malloc(x * sizeof(int *));
    if (a == O) return O;
    for (int i = 0; i < x; i++) {
        a[i] = malloc(y * sizeof(int));
        if (a[i] == O) {
            for (int j = 0; j < i; j++) free(a[j]);
            free(a);
            return O;
        }
    }
    return a;
}
int **adin4(int x, int y) {
    int **a = O;
    a = malloc(x * sizeof(int *));
    if (a == O) return O;
    for (int i = 0; i < x; i++) {
        a[i] = malloc(y * sizeof(int));
        if (a[i] == O) {
            for (int j = 0; j < i; j++) free(a[j]);
            free(a);
            return O;
        }
    }
    return a;
}
void input_a(int **a, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (scanf("%d", &a[i][j]) != 1) {
                printf("n/a\n");
                exit(1);
            }
        }
    }
}
void print_a(int **a, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%d", a[i][j]);
            if (j < y - 1) {
                printf(" ");
            }
        }
        if (i < x - 1) {
            printf("\n");
        }
    }
}

void free_a(int **a, int x) {
    for (int i = 0; i < x; i++) {
        free(a[i]);
    }
    free(a);
}
int main() {
    int method;
    int x, y;
    int *data;
    if (scanf("%d", &method) == 0 || method < 1 || method > 4) {
        printf("n/a\n");
        return 0;
    }
    if (scanf("%d %d", &x, &y) == 0 || x <= 0 || y <= 0 || (method == 1 && (x > MAX_SIZE || y > MAX_SIZE))) {
        printf("n/a\n");
        return 0;
    }
    int **a;
    if (method == 1) {
        int *a = adin1(x, y);
    }
    if (method == 2) {
        int **a = adin2(x, y);
    }
    if (method == 3) {
        int **a = adin3(x, y);
    }
    if (method == 4) {
        int **a = adin4(x, y);
    }
    if (a == O) {
        printf("n/a\n");
        return 0;
    }
    input_a(a, x, y);
    print_a(a, x, y);
    free_a(a, x);
    return 0;
}
