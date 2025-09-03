#include <stdio.h>
#define LEN 100

int input(int *a, int *n, int *b, int *m);
void sum(int *a, int n, int *b, int m, int *re, int *l);
void sub(int *a, int n, int *b, int m, int *re, int *l);
void output(int *re, int lo);

int main() {
    int a[LEN];
    int b[LEN];
    int re[LEN + 1];
    int n = 0, m = 0;
    int l = 0;
    if (input(a, &n, b, &m) == 0) {
        printf("n/a");
        return 0;
    }
    sum(a, n, b, m, re, &l);
    output(re, l);
    printf("\n");
    l = 0;
    sub(a, n, b, m, re, &l);
    if (l > 0) {
        output(re, l);
    } else {
        printf("n/a\n");
    }
    return 0;
}
int input(int *a, int *i, int *b, int *j) {
    char v;
    *i = 0;
    while ((v = getchar()) != '\n' && v != EOF) {
        if (v == ' ') {
            continue;
        }
        if (v >= '0' && v <= '9') {
            if (*i < 100) {
                a[(*i)++] = v - '0';
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
    *j = 0;
    while ((v = getchar()) != '\n' && v != EOF) {
        if (v == ' ') {
            continue;
        }
        if (v >= '0' && v <= '9') {
            if (*j < 100) {
                b[(*j)++] = v - '0';
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
    if (*i < *j) {
        return 0;
    }
    return 1;
}
void sum(int *a, int n, int *b, int m, int *re, int *l) {
    int carry = 0;
    int max_len = n > m ? n : m;

    for (int i = 0; i < max_len; i++) {
        int d1 = (i < n) ? a[n - 1 - i] : 0;
        int d2 = (i < m) ? b[m - 1 - i] : 0;
        int sum = d1 + d2 + carry;
        re[*l] = sum % 10;
        carry = sum / 10;
        (*l)++;
    }

    if (carry > 0) {
        re[*l] = carry;
        (*l)++;
    }
    for (int i = 0; i < (*l) / 2; i++) {
        int temp = re[i];
        re[i] = re[(*l) - 1 - i];
        re[(*l) - 1 - i] = temp;
    }
}
void sub(int *a, int n, int *b, int m, int *re, int *l) {
    if (n < m || (n == m && (a[0] < b[0]))) {
        *l = 0;
        return;
    }
    int r = 0;
    for (int i = 0; i < n; i++) {
        int d1 = a[n - 1 - i];
        int d2 = (i < m) ? b[m - 1 - i] : 0;
        if (d1 < d2 + r) {
            d1 += 10;
            re[*l] = d1 - d2 - r;
            r = 1;
        } else {
            re[*l] = d1 - d2 - r;
            r = 0;
        }
        (*l)++;
    }
    while (*l > 1 && re[*l - 1] == 0) {
        (*l)--;
    }
    for (int i = 0; i < (*l) / 2; i++) {
        int temp = re[i];
        re[i] = re[(*l) - 1 - i];
        re[(*l) - 1 - i] = temp;
    }
}
void output(int *re, int lo) {
    if (lo == 0) {
        printf("0\n");
        return;
    }
    printf("%d", re[0]);
    for (int i = 1; i < lo; i++) {
        printf(" %d", re[i]);
    }
}