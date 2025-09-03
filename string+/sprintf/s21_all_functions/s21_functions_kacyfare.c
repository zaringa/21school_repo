#include "../s21_string.h"

// №6. Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке,
// на которую указывает аргумент str.
char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;
  if (str != S21_NULL) {
    int i = 0;
    while (result == S21_NULL && (str[i] != '\0')) {
      if (str[i] == (unsigned char)c) {
        result = (char *)&str[i];
      }
      i++;
    }
    if (c == '\0' && result == S21_NULL) {
      result = (char *)&str[i];
    }
  }
  return result;
}

// №12. Находит первый символ в строке str1, который соответствует любому
// символу, указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  if (str1 != S21_NULL && str2 != S21_NULL) {
    int i = 0;
    while (result == S21_NULL && str1[i] != '\0') {
      int j = 0;
      while (result == S21_NULL && str2[j] != '\0') {
        if (str1[i] == str2[j]) {
          result = (char *)&str1[i];
        }
        j++;
      }
      i++;
    }
  }
  return result;
}

// №13. Выполняет поиск последнего вхождения символа c (беззнаковый тип) в
// строке, на которую указывает аргумент str.
char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;
  if (str != S21_NULL) {
    const char *last = str;
    while (*last != '\0') {
      if (*last == (char)c) {
        result = (char *)last;
      }
      last++;
    }
    if (c == '\0') {
      result = (char *)last;
    }
  }
  return result;
}

// №14. Находит первое вхождение всей строки needle (не включая завершающий
// нулевой символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  if (haystack != S21_NULL && needle != S21_NULL) {
    if (needle[0] == '\0') {
      result = (char *)haystack;
    } else {
      int i = 0;
      while (result == S21_NULL && haystack[i] != '\0') {
        int j = 0;
        int k = i;
        while (needle[j] != '\0' && haystack[k] != '\0' &&
               haystack[k] == needle[j]) {
          j++;
          k++;
        }
        if (needle[j] == '\0') {
          result = (char *)&haystack[i];
        }
        i++;
      }
    }
  }
  return result;
}

// №15. Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
  static char *last = S21_NULL;
  char *result = S21_NULL;
  if (delim == S21_NULL || (str == S21_NULL && last == S21_NULL) ||
      delim[0] == '\0') {
    last = S21_NULL;
  } else {
    if (str != S21_NULL) {
      last = str;
    }
    while (result == S21_NULL && *last != '\0') {
      if (s21_strchr(delim, *last) == S21_NULL) {
        result = last;
      } else {
        last++;
      }
    }
    if (result != S21_NULL) {
      int found_delim = 0;
      while (!found_delim && *last != '\0') {
        if (s21_strchr(delim, *last) != S21_NULL) {
          *last = '\0';
          last++;
          found_delim = 1;
        } else {
          last++;
        }
      }
    }
  }
  return result;
}
