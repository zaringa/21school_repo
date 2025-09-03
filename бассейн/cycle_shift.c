#include <stdio.h>
#define MAXN 10

int input(int *a, int *n, int *sd);
void sdvg(int *a, int n, int *b, int sd);
void output(int n, int *a);

int main() {
    int newdata[MAXN];
    int data[MAXN];
    int n, sd;
    if (input(data, &n, &sd) == 0) {
        printf("n/a\n");
        return 0;
    }
    sdvg(data, n, newdata, sd);
    output(n, newdata);
    return 0;
}
int input(int *a, int *n, int *sd) {
    if (scanf("%d", n) != 1 || *n <= 0 || *n > MAXN) {
        return 0;
    }
    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) != 1) {
            return 0;
        }
    }
    if (scanf("%d", sd) != 1) {
        return 0;
    }
    return 1;
}
void sdvg(int *a, int n, int *b, int sd) {
    sd %= n;
    int i = 0;
    for (int *p = b; p - b < n; p++) {
        if (sd <= 0) {
            *p = a[(i - sd) % n];
        } else {
            *p = a[(i + sd) % n];
        }
        i++;
    }
}
void output(int n, int *a) {
    printf("%d", a[0]);
    for (int i = 1; i < n; i++) {
        printf(" %d", a[i]);
    }
}