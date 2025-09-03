#include "../s21_string.h"

// 1. Возвращает копию строки (str), преобразованной в верхний регистр. В случае
// какой-либо ошибки следует вернуть значение S21_NULL.
void *s21_to_upper(const char *str) {
  char *result = S21_NULL;
  s21_size_t len = s21_strlen(str);
  result = (char *)calloc(len + 1, sizeof(char));
  if (result != S21_NULL) {
    for (s21_size_t i = 0; i < len; i++) {
      if (str[i] > 96 && str[i] < 123)
        result[i] = str[i] - 32;
      else
        result[i] = str[i];
    }
  }
  return (void *)result;
}

// 2. Возвращает копию строки (str), преобразованной в нижний регистр. В случае
// какой-либо ошибки следует вернуть значение S21_NULL.
void *s21_to_lower(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  s21_size_t len = s21_strlen(str);
  char *result = (char *)calloc(len + 1, sizeof(char));
  if (result == S21_NULL) {
    return S21_NULL;
  }
  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      result[i] = str[i] + 32;
    } else {
      result[i] = str[i];
    }
  }
  result[len] = '\0';
  return result;
}

// 3. Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию (start_index) в данной строке (src). В случае какой-либо
// ошибки следует вернуть значение S21_NULL.

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) return S21_NULL;

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index > src_len) return S21_NULL;

  char *result = calloc(src_len + str_len + 1, sizeof(char));
  if (!result) return S21_NULL;

  s21_strncpy(result, src, start_index);
  s21_strcat(result, str);
  s21_strcat(result, src + start_index);

  return result;
}
// 4.Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src). В
// случае какой-либо ошибки следует вернуть значение S21_NULL.
void *s21_trim(const char *src, const char *trim_chars) {
  if (!src) return S21_NULL;
  if (!trim_chars || !*trim_chars) trim_chars = " \t\n";

  s21_size_t len = s21_strlen(src);
  if (len == 0) {
    char *result = malloc(1);
    if (result) *result = '\0';
    return result;
  }

  s21_size_t start = 0;
  s21_size_t end = len - 1;
  while (start <= end && s21_strchr(trim_chars, src[start])) {
    start++;
  }
  while (end >= start && s21_strchr(trim_chars, src[end])) {
    end--;
  }

  s21_size_t new_len = (start > end) ? 0 : (end - start + 1);
  char *result = malloc(new_len + 1);
  if (!result) return S21_NULL;

  if (new_len > 0) {
    s21_strncpy(result, src + start, new_len);
  }
  result[new_len] = '\0';

  return result;
}
