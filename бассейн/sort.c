#include <stdio.h>

void inp(int *a, int n);
void sort(int *a, int n);

int main() {
    int n = 10;
    // scanf("%d", &n);
    int da[10];
    inp(da, n);
    sort(da, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", da[i]);
    }
}
void sort(int *a, int n) {
    for (int i = 1; i < n; i++) {
        int cur = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > cur) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = cur;
    }
}
void inp(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        scanf("%d", p);
    }
}
