#include "s21_string.h"

int s21_strlen(char *st) {
    char *p = st;
    while (*p != '\0') p++;
    return p - st;
}
int s21_strcmp(char *a1, char *a2) {
    int ch = 0;
    while ((*a1 != '\0' && *a2 != '\0') && (*a1 == *a2)) {
        a1++;
        a2++;
    }
    ch = (*a1 == *a2) ? 0 : (*a1 > *a2) ? 1 : -1;
    return ch;
}
int s21_strcpy(char *a, char *b) {
    int n = s21_strlen(a);
    int i = 0;
    char *p;
    for (p = b; p - b < n; p++) {
        *p = a[i];
        i++;
    }
    return 1;
}
int s21_strcat(char *a, char *b) {
    int n1 = s21_strlen(a);
    int n2 = s21_strlen(b);
    int i = 0;
    for (char *p = b + n2; p - a + n1 < n1; p++) {
        *p = a[i];
        i++;
    }
    return 1;
}
char *s21_strchr(char *a, char *b) {
    int n = s21_strlen(a) - 1;
    for (int i = 0; i < n; i++) {
        if (b[0] == a[i]) {
            int j = 0;
            while (b[j] == a[i + j]) {
                j++;
            }
            if (j == s21_strlen(b) - 1) {
                return &a[i];
            }
        }
    }
    return &a[n];
}
char *s21_strstr(char *a, char *b) {
    char *p = s21_strchr(a, b);
    char *n = "";
    int i = 0;
    for (n = a; n - p > 0; n++) {
        n[i] = a[i];
        i++;
    }
    return n;
}

char *s21_strtok(char *a, const char *b) {
    const char *save = b;
    char *p = a;
    p++;
    if (b == save) return p;
    p++;
    return p;
}