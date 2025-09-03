#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    input(data, &n);
    squaring(data, n);
    output(data, n);

    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) == 0 || *n < 1 || *n > NMAX) {
        return 0;
    }
    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) != 1) {
            return 0;
        }
    }
}

void output(int *a, int n) {
    printf("%d", *a);
    for (int *p = a + 1; p - a < n; p++) {
        printf(" %d", *p);
    }
}

void squaring(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        *p *= *p;
    }
}
