#include <stdio.h>
#include <stdlib.h>
#define O NULL
int input(int **a, int *x, int *y);
void free_a(int **a, int x);
void output(int **a, int x, int y);
int **adin2(int x, int y);
int **adin3(int x, int y);
int **adin4(int x, int y);
void bobr(int *arr, int x, int y, int **a);

int fut(int **a, int x, int y) {
    int *arr = malloc(y * sizeof(int));
    int sum = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            sum += a[i][j];
        }
        arr[i] = sum;
    }
    bobr(arr, x, y, a);
}

void bobr(int *arr, int x, int y, int **a) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < y - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                for (int l = 0; l < x; l++) {
                    int t = a[l][j + 1];
                    a[l][j + 1] = a[l][j];
                    a[l][j] = t;
                    for (int k = 0; k < x; k++) {
                        int t = arr[k];
                        arr[k] = arr[k + 1];
                        arr[k + 1] = t;
                    }
                }
            }
        }
    }
}
int main() {
    int method;
    int x, y;
    int *arr;
    if (scanf("%d", &method) == 0 || method < 1 || method > 3) {
        printf("n/a\n");
        return 0;
    }
    /*if (scanf("%d %d", &x, &y) ==0 || x <= 0 || y <= 0 || (method == 1 && (x > MAX_SIZE || y > MAX_SIZE))) {
        printf("n/a\n");
        return 0;
    }*/
    int **a;
    if (method == 1) {
        int **a = adin2(x, y);
    }
    if (method == 2) {
        int **a = adin3(x, y);
    }
    if (method == 3) {
        int **a = adin4(x, y);
    }
    if (a == O) {
        printf("n/a\n");
        return 0;
    }
    input(a, &x, &y);
    fut(a, x, y);
    output(a, x, y);
    free_a(a, x);
    return 0;
}

int input(int **a, int *x, int *y) {
    if (scanf("%d %d", x, y) == 0) {
        return 0;
    }
    for (int i = 0; i < *x; i++) {
        for (int j = 0; j < *y; j++) {
            if (scanf("%d", &(a[i][j])) != 1) {
                printf("n/a\n");
                return 0;
            }
        }
    }
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

void free_a(int **a, int x) {
    for (int i = 0; i < x; i++) {
        free(a[i]);
    }
    free(a);
}