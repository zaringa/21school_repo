#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    input(data, &n);
    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) == 0 || *n < 1 || *n > NMAX) {
        return 0;
    }
    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) == 0) {
            printf("n/a\n");
            return 0;
        }
    }
}
void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d ", *p);
    }
    printf("\n");
}
int max(int *a, int n) {
    int mx = *a;
    for (int *p = a; p - a < n; p++) {
        if (mx > *p) mx = *p;
    }
    return mx;
}
int min(int *a, int n) {
    int mi = *a;
    for (int *p = a; *p - *a < n; p++) {
        if (mi < *p) mi = *p;
    }
    return mi;
}
double mean(int *a, int n) {
    double sum = 0;
    for (int *p = a; p - a < n; p++) {
        sum += *p;
    }
    sum /= n;
    return (sum);
}
double variance(int *a, int n) {
    double sumk = 0;
    double sum = mean(a, n);
    for (int *p = a; p - a < n; p++) {
        sumk += ((*p - sum) * (*p - sum));
    }
    sumk /= n;
    return sumk;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6f %.6f\n", max_v, min_v, mean_v, variance_v);
}