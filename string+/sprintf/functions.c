#include <math.h>
#include <wchar.h>
#include <wctype.h>

#include "../s21_string.h"
#include "defs.h"
#include "grisu/grisu3.h"

void get_uint_string_with_base(char *buf, unsigned long long num,
                               int is_negative, int base, int is_uppercase,
                               struct token *token, int *length);

int write_chars_into_buf(struct token *token, char *buf, char *str,
                         int str_size, char empty_field_symbol);

long long llabs(long long n);

#define DEFINE_VALUE_GETTER(name, return_value, default_type, h_type,       \
                            h_type_cast_to, i_type, i_type_cast_to, l_type, \
                            l_type_cast_to)                                 \
  static inline return_value name(struct token *token, va_list *args) {     \
    if (token->lm == LM_i) return (i_type_cast_to)va_arg(*args, i_type);    \
    if (token->lm == LM_L) return (l_type_cast_to)va_arg(*args, l_type);    \
    if (token->lm == LM_h) return (h_type_cast_to)va_arg(*args, h_type);    \
    return va_arg(*args, default_type);                                     \
  }

DEFINE_VALUE_GETTER(get_signed_value, long long, int, int, short, long, long,
                    int, int)
DEFINE_VALUE_GETTER(get_unsigned_value, unsigned long long, unsigned int,
                    unsigned int, unsigned short, unsigned long, unsigned long,
                    unsigned int, unsigned int)
DEFINE_VALUE_GETTER(get_floating_point_value, long double, double, double,
                    double, double, double, long double, long double)

long long llabs(long long n) { return (n < 0 ? -n : n); }

void shift_by_one(char *buf, int length, int start_pos) {
  char digit = buf[start_pos];

  for (int i = start_pos; i <= length; ++i) {
    char temp = buf[i + 1];
    buf[i + 1] = digit;
    digit = temp;
  }
  buf[start_pos] = ' ';
}

void shift_by_count(char *buf, int length, int start_pos, int count) {
  for (int i = 0; i < count; ++i) {
    shift_by_one(buf, length, start_pos);
    length++;
  }
}

void rewrite_number_in_decimal(struct token *token, char *buf, int *length,
                               int dot_position, int is_negative) {
  int count_of_zeros_after_num = 0;
  if (dot_position <= 0) {
    shift_by_count(buf, *length, 0, -dot_position + 2);
    *length += -dot_position + 2;

    buf[0] = '0';
    buf[1] = '.';
    count_of_zeros_after_num =
        MAX(count_of_zeros_after_num, token->precision - (*length - 2));
  } else {
    shift_by_one(buf, *length, dot_position);
    (*length)++;

    buf[dot_position] = '.';
    count_of_zeros_after_num =
        MAX(count_of_zeros_after_num,
            token->precision - (*length - 1 - dot_position));
  }

  shift_by_count(buf, *length, *length, count_of_zeros_after_num);
  for (int i = *length; i < *length + count_of_zeros_after_num; ++i) {
    buf[i] = '0';
  }
  *length += count_of_zeros_after_num;

  int is_need_sign = ((token->flags & PLUS) || is_negative);
  char sign = (is_negative ? '-' : '+');
  if (!is_need_sign && (token->flags & SPACE)) {
    is_need_sign = 1;
    sign = ' ';
  }

  if (is_need_sign) {
    shift_by_one(buf, *length, 0);
    (*length)++;

    buf[0] = sign;
  }
}

void rewrite_number_in_sceintific(struct token *token, char *buf, int *length,
                                  int decimal_exponent, int is_upper,
                                  int is_negative) {
  shift_by_one(buf, *length, 1);
  (*length)++;

  buf[1] = '.';

  int count_of_zeros_after_num = MAX(0, token->precision - (*length - 2));
  shift_by_count(buf, *length, *length, count_of_zeros_after_num);
  for (int i = 0; i < count_of_zeros_after_num; ++i) {
    buf[i + *length] = '0';
  }

  *length += count_of_zeros_after_num;
  shift_by_one(buf, *length, *length);
  (*length)++;

  buf[*length - 1] = (is_upper ? 'E' : 'e');

  struct token token_for_exponent;
  token_for_exponent.size_of_token = NOT_SPECIFIED;
  token_for_exponent.field_size = 2;
  token_for_exponent.flags = PLUS | ZERO;
  token_for_exponent.precision = 2;

  int output_exponent =
      decimal_exponent + *length - count_of_zeros_after_num - 3;
  int res_length;
  char decimal_exponent_str[20];
  get_uint_string_with_base(decimal_exponent_str, llabs(output_exponent),
                            output_exponent < 0, 10, 0, &token_for_exponent,
                            &res_length);

  s21_strcpy(buf + *length, decimal_exponent_str);
  *length += res_length;

  int is_need_sign = ((token->flags & PLUS) || is_negative);
  char sign = (is_negative ? '-' : '+');
  if (!is_need_sign && (token->flags & SPACE)) {
    is_need_sign = 1;
    sign = ' ';
  }

  if (is_need_sign) {
    shift_by_one(buf, *length, 0);
    (*length)++;

    buf[0] = sign;
  }
}

int get_uint_len(unsigned long long num, int base) {
  int len = 0;
  if (num == 0) len = 1;
  while (num) {
    len++;
    num /= base;
  }

  return len;
}

int get_additional_size(int base) {
  int res = 0;
  switch (base) {
    case 8:
      res = 1;
      break;
    case 16:
      res = 2;
      break;
  }

  return res;
}

void write_additional_values(char *buf, int base, int is_uppercase) {
  if (base == 8) {
    buf[0] = '0';
  } else if (base == 16) {
    buf[0] = '0';
    buf[1] = (is_uppercase ? 'X' : 'x');
  }
}

int format_uint_with_base(struct token *token, char *buf,
                          unsigned long long num, int is_negative,
                          int is_uppercase, int base) {
  char empty_field_symbol =
      ((token->flags & ZERO) && !(token->flags & MINUS) ? '0' : ' ');

  int length;
  char buf_for_int[20];
  get_uint_string_with_base(buf_for_int, num, is_negative, base, is_uppercase,
                            token, &length);
  int res =
      write_chars_into_buf(token, buf, buf_for_int, length, empty_field_symbol);

  return res;
}

void get_uint_string_with_base(char *buf, unsigned long long num,
                               int is_negative, int base, int is_uppercase,
                               struct token *token, int *length) {
  const char *lower_alphabet = "0123456789abcdef";
  const char *upper_alphabet = "0123456789ABCDEF";
  const char *alphabet = (is_uppercase ? upper_alphabet : lower_alphabet);

  int len = get_uint_len(num, base);

  int is_need_sign = ((token->flags & PLUS) || is_negative);
  char sign = (is_negative ? '-' : '+');

  if (!is_need_sign && (token->flags & SPACE)) {
    is_need_sign = 1;
    sign = ' ';
  }

  int additional = 0;
  if (base != 10 && (token->flags & NUMBER_SIGN)) {
    additional = get_additional_size(base);
  }

  buf[MAX(len, token->precision) + is_need_sign + additional] = '\0';

  *length = MAX(len, token->precision) + is_need_sign + additional;

  if (additional != 0) write_additional_values(buf, base, is_uppercase);

  for (int i = MAX(len, token->precision) + is_need_sign + additional - 1;
       i >= additional; --i) {
    buf[i] = alphabet[num % base];
    num /= base;
  }

  if (is_need_sign) buf[0] = sign;
}

int write_chars_into_buf(struct token *token, char *buf, char *str,
                         int str_size, char empty_field_symbol) {
  int offset = MAX(0, token->field_size - str_size);

  if (!(token->flags & MINUS)) {
    for (int i = 0; i < offset; ++i) {
      buf[i] = empty_field_symbol;
    }

    for (int i = offset; i < offset + str_size; ++i) {
      buf[i] = str[i - offset];
    }
  } else {
    for (int i = 0; i < str_size; ++i) {
      buf[i] = str[i];
    }

    for (int i = str_size; i < str_size + offset; ++i) {
      buf[i] = empty_field_symbol;
    }
  }

  return offset + str_size;
}

int convert_wide_char_to_char(char *buf, wchar_t *src) {
  wchar_t *ch = src;

  char *buf_copy = buf;
  while (*ch != L'\0') {
    int convert_res = wcrtomb(buf_copy, *ch, NULL);
    buf_copy += convert_res;
    ++ch;
  }

  return buf_copy - buf;
}

int format_CHARACTER(char *buf, struct token *token, va_list *args) {
  char output_buf[4096] = {0};
  int size = 0;

  token->flags = 0;

  switch (token->lm) {
    case LM_i: {
      wchar_t wc_buf[2] = {0};
      wc_buf[0] = va_arg(*args, wint_t);
      size = convert_wide_char_to_char(output_buf, wc_buf);
      break;
    }
    default: {
      char ch_char = va_arg(*args, int);
      output_buf[0] = ch_char;
      size = 1;
    }
  }

  int res = write_chars_into_buf(token, buf, output_buf, size, ' ');

  return res;
}

int format_STRING(char *buf, struct token *token, va_list *args) {
  char temp_buf[4096] = {0};
  int size = 0;

  char *output_buf;

  token->flags = 0;

  switch (token->lm) {
    case LM_i: {
      wchar_t *ch = va_arg(*args, wchar_t *);
      size = convert_wide_char_to_char(temp_buf, ch);
      output_buf = temp_buf;
      break;
    }
    default: {
      char *ch = va_arg(*args, char *);
      size = s21_strlen(ch);
      output_buf = ch;
    }
  }

  if (token->precision != NOT_SPECIFIED) {
    size = MIN(token->precision, size);
  }

  int res = write_chars_into_buf(token, buf, output_buf, size, ' ');

  return res;
}

int format_DECIMAL_SIGNED_INTEGER(char *buf, struct token *token,
                                  va_list *args) {
  long long value = get_signed_value(token, args);
  return format_uint_with_base(token, buf, llabs(value), value < 0, 0, 10);
}

int format_OCTAL_UNSIGNED_INTEGER(char *buf, struct token *token,
                                  va_list *args) {
  unsigned long long value = get_unsigned_value(token, args);

  token->flags &= ~PLUS;
  token->flags &= ~SPACE;

  return format_uint_with_base(token, buf, value, 0, 0, 8);
}

int format_HEXADECIMAL_UNSIGNED_INTEGER_UPPER(char *buf, struct token *token,
                                              va_list *args) {
  unsigned long long value = get_unsigned_value(token, args);

  token->flags &= ~PLUS;
  token->flags &= ~SPACE;

  return format_uint_with_base(token, buf, value, 0, 1, 16);
}

int format_HEXADECIMAL_UNSIGNED_INTEGER_LOWER(char *buf, struct token *token,
                                              va_list *args) {
  unsigned long long value = get_unsigned_value(token, args);

  token->flags &= ~PLUS;
  token->flags &= ~SPACE;

  return format_uint_with_base(token, buf, value, 0, 0, 16);
}

int format_DECIMAL_UNSIGNED_INTEGER(char *buf, struct token *token,
                                    va_list *args) {
  unsigned long long value = get_unsigned_value(token, args);

  return format_uint_with_base(token, buf, value, 0, 0, 10);
}

int format_DECIMAL_FLOAT_NUMBER(char *buf, struct token *token, va_list *args) {
  double value = get_floating_point_value(token, args);
  char buf_for_fp[512];
  int length;
  int decimal_exponent;

  if (token->precision == NOT_SPECIFIED) {
    token->precision = 6;
  }

  grisu3(fabs(value), buf_for_fp, &length, &decimal_exponent);
  rewrite_number_in_decimal(token, buf_for_fp, &length,
                            length + decimal_exponent, value < 0);

  return write_chars_into_buf(token, buf, buf_for_fp, length, ' ');
}

int format_DECIMAL_EXPONENT_FLOAT_NUMBER_UPPER(char *buf, struct token *token,
                                               va_list *args) {
  double value = get_floating_point_value(token, args);
  char buf_for_fp[512];
  int length;
  int decimal_exponent;

  if (token->precision == NOT_SPECIFIED) {
    token->precision = 6;
  }

  grisu3(fabs(value), buf_for_fp, &length, &decimal_exponent);
  rewrite_number_in_sceintific(token, buf_for_fp, &length, decimal_exponent, 1,
                               value < 0);

  return write_chars_into_buf(token, buf, buf_for_fp, length, ' ');
}

int format_DECIMAL_EXPONENT_FLOAT_NUMBER_LOWER(char *buf, struct token *token,
                                               va_list *args) {
  double value = get_floating_point_value(token, args);

  char buf_for_fp[512];
  int length;
  int decimal_exponent;

  if (token->precision == NOT_SPECIFIED) {
    token->precision = 6;
  }

  grisu3(fabs(value), buf_for_fp, &length, &decimal_exponent);
  rewrite_number_in_sceintific(token, buf_for_fp, &length, decimal_exponent, 0,
                               value < 0);

  return write_chars_into_buf(token, buf, buf_for_fp, length, ' ');
}

int format_DEPENDING_FLOAT_NUMBER_UPPER(char *buf, struct token *token,
                                        va_list *args) {
  double value = get_floating_point_value(token, args);

  char buf_for_fp[512];
  int length = 0;
  int decimal_exponent = 0;

  if (token->precision == NOT_SPECIFIED) {
    token->precision = 6;
  }

  if (token->precision == 0) {
    token->precision = 1;
  }

  grisu3(fabs(value), buf_for_fp, &length, &decimal_exponent);
  int final_exponent = decimal_exponent - (length - 1);

  if (token->precision > final_exponent && final_exponent >= -4) {
    token->precision = token->precision - final_exponent - 1;
    rewrite_number_in_decimal(token, buf_for_fp, &length,
                              length + decimal_exponent, value < 0);
  } else {
    token->precision -= 1;
    rewrite_number_in_sceintific(token, buf_for_fp, &length, decimal_exponent,
                                 1, value < 0);
  }

  return write_chars_into_buf(token, buf, buf_for_fp, length, ' ');
}

int format_DEPENDING_FLOAT_NUMBER_LOWER(char *buf, struct token *token,
                                        va_list *args) {
  double value = get_floating_point_value(token, args);

  char buf_for_fp[512];
  int length = 0;
  int decimal_exponent = 0;

  if (token->precision == NOT_SPECIFIED) {
    token->precision = 6;
  }

  if (token->precision == 0) {
    token->precision = 1;
  }

  int final_exponent = decimal_exponent - (length - 1);
  grisu3(fabs(value), buf_for_fp, &length, &decimal_exponent);

  if (token->precision > final_exponent && final_exponent >= -4) {
    token->precision = token->precision - final_exponent - 1;
    rewrite_number_in_decimal(token, buf_for_fp, &length,
                              length + decimal_exponent, value < 0);
  } else {
    token->precision -= 1;
    rewrite_number_in_sceintific(token, buf_for_fp, &length, decimal_exponent,
                                 1, value < 0);
  }

  return write_chars_into_buf(token, buf, buf_for_fp, length, ' ');
}

int format_NUMBER_OF_CHARACTERS(char *buf, struct token *token, va_list *args) {
  void *ptr = va_arg(*args, void *);
  (void)buf;

  int value = token->current_count_of_bytes;
  switch (token->lm) {
    case LM_h: {
      *(short *)ptr = value;
      break;
    }
    case LM_i: {
      *(long *)ptr = value;
      break;
    }
    default: {
      *(int *)ptr = value;
    }
  }
  return 1;
}

int format_POINTER(char *buf, struct token *token, va_list *args) {
  void *value = va_arg(*args, void *);

  uint64_t addr = (uint64_t)(uintptr_t)value;

  token->flags |= NUMBER_SIGN;

  int length;
  char formatted_num[20];
  get_uint_string_with_base(formatted_num, addr, 0, 16, 0, token, &length);
  int res = write_chars_into_buf(token, buf, formatted_num, length, ' ');

  return res;
}

int format_PERCENT_CHARACTER(char *buf, struct token *token, va_list *args) {
  *buf = '%';
  (void)token;
  (void)args;
  return 1;
}
