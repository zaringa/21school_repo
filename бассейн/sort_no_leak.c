#include <stdio.h>
#include <stdlib.h>

int input(int *a, int n);
void sort(int *a, int n);
void output(int *a, int n);

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("n/a");
        return 0;
    }
    int *a = malloc(sizeof(n));
    if (input(a, n) == 0) {
        printf("n/a");
        return 0;
    }
    sort(a, n);
    output(a, n);
}
int input(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        if (scanf("%d", p) != 1) {
            return 0;
        }
    }
}
void sort(int *a, int n) {
    for (int *p = a + 1; p - a < n; p++) {
        int cur = *p;
        int j = p - a - 1;
        while (j >= 0 && *(a + j) > cur) {
            *(a + j + 1) = *(a + j);
            j--;
        }
        *(a + j + 1) = cur;
    }
}

void output(int *a, int n) {
    printf("%d", *a);
    for (int *p = a + 1; p - a < n; p++) {
        printf(" %d", *p);
    }
    free(a);
}