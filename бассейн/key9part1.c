#include <stdio.h>
#define MAXN 10

int input(int *a, int *n);
void output(int sum, int *newa, int n);
int sum_numbers(int *a, int n, int *sum);
int find_numbers(int *a, int n, int *newn, int *da, int sum);

int main() {
    int data[MAXN];
    int newdata[MAXN];
    int n, newn = 0, sum = 0;

    if (input(data, &n) == 0 || sum_numbers(data, n, &sum) == 0 || sum == 0 ||
        find_numbers(data, n, &newn, newdata, sum) == 0) {
        printf("n/a\n");
        return 0;
    }
    output(sum, newdata, newn);
    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || *n <= 0 || *n > MAXN) {
        return 0;
    }
    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) != 1) {
            return 0;
        }
    }
    return 1;
}
int sum_numbers(int *a, int n, int *sum) {
    int count = 0;
    *sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            *sum += a[i];
            count++;
        }
    }
    return count;
}
int find_numbers(int *a, int n, int *newn, int *da, int sum) {
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0 && sum % a[i] == 0) {
            da[j] = a[i];
            j++;
        }
    }
    *newn = j;
    return j;
}
void output(int sum, int *newa, int n) {
    printf("%d\n", sum);
    printf("%d", newa[0]);
    for (int i = 1; i < n; i++) {
        printf(" %d", newa[i]);
    }
}