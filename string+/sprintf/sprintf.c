#include <limits.h>
#include <regex.h>
#include <stdarg.h>
#include <stdlib.h>

#include "defs.h"
#include "flat_map/flat_map.h"

int parse_flags(const char *format);
int get_width_of_field(const char *format, va_list *args);
int get_precision(const char *format, va_list *args);
int get_count_of_flags(int flags);
length_modifiers parse_length_modifier(const char *format, int size_of_token);
int get_length_of_token(const char *format);
unsigned char parse_type(const char *format, int size_of_token);

struct token init_token(const char *format, va_list *args) {
  struct token token;
  token.size_of_token = get_length_of_token(format);
  if (token.size_of_token != -1) {
    token.flags = parse_flags(format + 1);
    int flags_count = get_count_of_flags(token.flags);
    token.lm = parse_length_modifier(format, token.size_of_token);
    token.field_size = get_width_of_field(format + flags_count + 1, args);
    token.precision = get_precision(format + flags_count + 1, args);
    token.type = parse_type(format, token.size_of_token);
    token.current_count_of_bytes = 0;
  }

  return token;
}

unsigned char parse_type(const char *format, int size_of_token) {
  return *(format + size_of_token - 1);
}

length_modifiers parse_length_modifier(const char *format, int size_of_token) {
  length_modifiers result = LM_NO_MODIFIER;
  char lm = *(format + size_of_token - 2);

  if (lm == 'L') {
    result = LM_L;
  } else if (lm == 'l') {
    result = LM_i;
  } else if (lm == 'h') {
    result = LM_h;
  }

  return result;
}

int get_length_of_token(const char *format) {
  regex_t *regex = (regex_t *)malloc(sizeof(regex_t));
  int func_res = NOT_SPECIFIED;
  int comp_res = regcomp(regex, REGULAR_EXPRESSION_FOR_TOKEN, REG_EXTENDED);

  if (!comp_res) {
    regmatch_t match[1];
    if (!regexec(regex, format, 1, match, 0)) {
      func_res = match[0].rm_eo;
    }

    regfree(regex);
    free(regex);
  }

  return func_res;
}

int parse_flag(char flag) {
  int res = 0;
  switch (flag) {
    case '-':
      res = MINUS;
      break;
    case '+':
      res = PLUS;
      break;
    case ' ':
      res = SPACE;
      break;
    case '#':
      res = NUMBER_SIGN;
      break;
    case '0':
      res = ZERO;
      break;
  }

  return res;
}

int parse_flags(const char *format) {
  int flags = 0;
  while (*format != '\0' && IS_FLAG(*format)) {
    flags |= parse_flag(*format);
    format++;
  }

  return flags;
}

int get_count_of_flags(int flags) {
  int res = 0;
  while (flags) {
    if (flags % 2 == 1) res++;
    flags >>= 1;
  }

  return res;
}

int get_number(const char *str) {
  int res = 0;
  while (IS_NUMBER(*str)) {
    res = res * 10 + (*str - '0');
    str++;
  }
  return res;
}

int get_width_of_field(const char *format, va_list *args) {
  int res = NOT_SPECIFIED;
  if (*format == '*')
    res = va_arg(*args, int);
  else if (IS_NUMBER(*format))
    res = get_number(format);

  return res;
}

int get_precision(const char *format, va_list *args) {
  int res = NOT_SPECIFIED;
  if (*format == '*') {
    format++;
  } else {
    while (IS_NUMBER(*format)) format++;
  }

  if (*format == '.' && IS_NUMBER(*(format + 1))) res = get_number(format + 1);
  if (*format == '.' && *(format + 1) == '*') res = va_arg(*args, int);

  return res;
}

__attribute__((format(printf, 2, 3))) void s21_sprintf(char *buf,
                                                       const char *format,
                                                       ...) {
  va_list args;
  va_start(args, format);

  struct flat_map map;
  init_flat_map(&map);

  int count_of_bytes = 0;
  while (*format != '\0') {
    if (*format == '%') {
      struct token token = init_token(format, &args);
      format_function format_func = get_function(&map, token.type);
      token.current_count_of_bytes = count_of_bytes;
      int bytes = format_func(buf, &token, &args);
      buf += bytes;
      count_of_bytes += bytes;
      format += token.size_of_token - 1;
    } else {
      *buf = *format;
      ++buf;
    }
    format++;
  }

  *buf = *format;
  va_end(args);
}
