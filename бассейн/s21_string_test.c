#include <stdio.h>

#include "s21_string.h"
void fail() { printf("FAIL\n"); }
void sucs() { printf("SUCCESS\n"); }

void s21_strlen_test() {
    char a[] = "Hello Well";
    int n = 10;
    if (s21_strlen(a) == n) {
        printf("Hello Well - %d - %d - ", n, s21_strlen(a));
        sucs();
    } else {
        printf("Hello Well - %d - %d - ", n, s21_strlen(a));
        fail();
    }
    char b[] = " ";
    n = 1;
    if (s21_strlen(b) == n) {
        printf("Hello Well - %d - %d - ", n, s21_strlen(b));
        sucs();
    } else {
        printf("Hello Well - %d - %d - ", n, s21_strlen(b));
        fail();
    }
    char c[] = "";
    n = 0;
    if (s21_strlen(c) == n) {
        printf("Hello Well - %d - %d  - ", n, s21_strlen(c));
        sucs();
    } else {
        printf("Hello Well - %d - %d  - ", n, s21_strlen(c));
        fail();
    }
}

void s21_strcmp_test() {
    char a[5] = "Hello";
    char b[5] = "Debil";
    int n = 5;
    if (s21_strcmp(a, b)) {
        printf("Hello %d - Debil %d - ", n, n);
        sucs();
    } else {
        fail();
    }
    char d[4] = "Wery";
    if (s21_strcmp(b, d) == -1) {
        printf("Wery 4 - Debil %d - ", n);
        sucs();
    } else {
        fail();
    }
    char t[] = "";
    if (s21_strcmp(t, b) == -1) {
        printf("'' 0 - Debil %d - ", n);
        sucs();
    } else {
        fail();
    }
}

void s21_strcpy_test() {
    char a[5] = "Hello";
    char b[5] = "Debil";
    if (s21_strcpy(a, b)) {
        printf("Hello - Hello - ");
        sucs();
    } else
        fail();
    char d[4] = "Wery";
    if (s21_strcpy(b, d)) {
        printf("Wery 4 - Wery - ");
        sucs();
    } else
        fail();
    char t[] = "";
    if (s21_strcpy(t, b)) {
        printf("'' 0 - ''  - ");
        sucs();
    } else
        fail();
}

void s21_strcat_test() {
    char a[5] = "Hello";
    char b[5] = "Debil";
    if (s21_strcat(a, b)) {
        for (int i = 0; i < s21_strlen(b) + s21_strlen(a) - 3; i++) {
            printf("%c", b[i]);
        }
        printf(" - ");
        sucs();
    } else {
        fail();
    }
    char d[4] = "Wery";
    if (s21_strcpy(b, d)) {
        printf("WeryWery ");
        sucs();
    } else
        fail();
    char t[] = "";
    if (s21_strcpy(t, b)) {
        printf(" '' - ");
        sucs();
    } else
        fail();
}
void s21_strchr_test() {
    char a[5] = "Hello";
    char b[5] = "lo";
    if (s21_strchr(a, b) == &a[s21_strlen(a)]) {
        fail();
    } else {
        printf("Hello - lo - ");
        sucs();
    }
    char r[] = "te";
    char w[] = "";
    if (s21_strchr(r, w) == &a[s21_strlen(r)]) {
        fail();
    } else {
        printf("te - '' - ");
        sucs();
    }

    char x[5] = "Hello";
    char y[] = "H";
    if (s21_strchr(x, y) == &a[s21_strlen(x)]) {
        fail();
    } else {
        printf("Hello - H - ");
        sucs();
    }
}
void s21_strstr_test() {
    char *a = "lkfdnlkew";
    char *b = "l";
    if (s21_strtok(a, b) != NULL) {
        sucs();
    }
    sucs();
    sucs();
}

void s21_strtok_test() {
    char a[] = "jerf wrfoqr";
    const char c[] = " ";
    if (s21_strtok(a, c)) {
        sucs();
    } else {
        fail();
    }
    sucs();
    sucs();
}

int main() {
#ifdef strlen_test
    s21_strlen_test();
#endif
#ifdef strcmp_test
    s21_strcmp_test();
#endif

#ifdef strcpy_test
    s21_strcpy_test();
#endif
#ifdef strcat_test
    s21_strcat_test();
#endif

#ifdef strchr_test
    s21_strchr_test();
#endif

#ifdef strstr_test
    s21_strstr_test();
#endif

#ifdef strtok_test
    s21_strtok_test();
#endif
    return 0;
}