#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
void output(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == 0) {
        printf("n/a\n");
        return 0;
    }
    output(data, n);
    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || *n < 1 || *n > NMAX) {
        return 0;
    }
    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) != 1) {
            return 0;
        }
    }
    return 1;
}

void output(int *a, int n) {
    double m = mean(a, n);
    double var = variance(a, n);
    double threshold = m + 3 * sqrt(var);
    for (int *p = a; p - a < n; p++) {
        if (*p != 0) {
            if (*p % 2 == 0 && *p >= m && *p <= threshold) {
                printf("%d\n", *p);
            }
        }
    }
}
double mean(int *a, int n) {
    double sum = 0;
    for (int *p = a; p - a < n; p++) {
        sum += *p;
    }
    return sum / n;
}
double variance(int *a, int n) {
    double sumk = 0;
    double m = mean(a, n);
    for (int *p = a; p - a < n; p++) {
        sumk += ((*p - m) * (*p - m));
    }
    return sumk / n;
}