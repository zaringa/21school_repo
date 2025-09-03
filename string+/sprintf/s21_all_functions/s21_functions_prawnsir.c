#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  if (str == S21_NULL) return S21_NULL;
  const unsigned char *p = str;
  unsigned char uc = (unsigned char)c;
  for (; n--; p++) {
    if (*p == uc) return (void *)p;
  }
  return S21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = str1;
  const unsigned char *s2 = str2;
  while (n-- > 0) {
    if (*s1 != *s2) return *s1 - *s2;
    s1++;
    s2++;
  }
  return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *d = dest;
  const char *s = src;
  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *p = str;
  for (s21_size_t i = 0; i < n; i++) {
    p[i] = (unsigned char)c;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *orig_dest = dest;

  while (*dest) dest++;

  while (n-- && (*dest++ = *src++));

  return orig_dest;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  while (n > 0 && *str1 && (*str1 == *str2)) {
    str1++;
    str2++;
    n--;
  }
  if (n == 0) {
    return 0;
  }
  if (*str1 > *str2) return 1;
  return -1;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (dest == S21_NULL || src == S21_NULL) return dest;

  char *orig_dest = dest;
  s21_size_t i;

  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  for (; i < n; i++) {
    dest[i] = '\0';
  }

  return orig_dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  if (str1 == S21_NULL || str2 == S21_NULL) {
    return 0;
  }

  s21_size_t len = 0;

  for (; *str1 != '\0'; str1++, len++) {
    const char *r = str2;
    for (; *r != '\0'; r++) {
      if (*str1 == *r) {
        return len;
      }
    }
  }

  return len;
}
s21_size_t s21_strlen(const char *str) {
  s21_size_t count = 0;
  while (*str != '\0') {
    str++;
    count++;
  }
  return count;
}

char *s21_strcpy(char *dest, const char *src) {
  if (dest == S21_NULL || src == S21_NULL) return dest;

  char *ptr = dest;
  while ((*ptr++ = *src++));

  return dest;
}

char *s21_strcat(char *dest, const char *src) {
  char *ptr = dest;
  while (*ptr != '\0') {
    ptr++;
  }
  while (*src != '\0') {
    *ptr++ = *src++;
  }
  *ptr = '\0';

  return dest;
}