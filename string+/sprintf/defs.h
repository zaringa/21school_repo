#ifndef DEFS_H
#define DEFS_H

#include <stdarg.h>
#include <stdint.h>

typedef enum { LM_NO_MODIFIER, LM_h, LM_i, LM_L } length_modifiers;

struct token {
  char type;
  int flags;
  length_modifiers lm;
  int field_size;
  int precision;
  int size_of_token;

  int current_count_of_bytes;
};

typedef int (*format_function)(char *, struct token *, va_list *);
#define REGULAR_EXPRESSION_FOR_TOKEN \
  "^%([-+ #0]+)?([*]|[0-9]+)?(\\.[*]|\\.[0-9]+)?([lLh])?[diuoxXfFeEgGcspn]"

#define MINUS 1
#define PLUS 2
#define SPACE 4
#define NUMBER_SIGN 8
#define ZERO 16

#define CHAR_COUNT (1 << (sizeof(char) * 8))

#define IS_ALPHABET(x) ((x) >= 'a' && (x) <= 'z');
#define IS_FLAG(x) \
  ((x) == '-' || (x) == '+' || (x) == ' ' || (x) == '#' || (x) == '0')
#define IS_NUMBER(x) ((x) >= '0' && (x) <= '9')
#define IS_MODIFIER(x) ((x) == 'h' || (x) == 'i' || (x) == 'L')

#define TYPES_LIST(X)                         \
  X(CHARACTER, 'c')                           \
  X(STRING, 's')                              \
  X(DECIMAL_SIGNED_INTEGER, 'd')              \
  X(OCTAL_UNSIGNED_INTEGER, 'o')              \
  X(HEXADECIMAL_UNSIGNED_INTEGER_UPPER, 'X')  \
  X(HEXADECIMAL_UNSIGNED_INTEGER_LOWER, 'x')  \
  X(DECIMAL_UNSIGNED_INTEGER, 'u')            \
  X(DECIMAL_FLOAT_NUMBER, 'f')                \
  X(DECIMAL_EXPONENT_FLOAT_NUMBER_UPPER, 'E') \
  X(DECIMAL_EXPONENT_FLOAT_NUMBER_LOWER, 'e') \
  X(DEPENDING_FLOAT_NUMBER_UPPER, 'G')        \
  X(DEPENDING_FLOAT_NUMBER_LOWER, 'g')        \
  X(NUMBER_OF_CHARACTERS, 'n')                \
  X(POINTER, 'p')                             \
  X(PERCENT_CHARACTER, '%')

#define GENERATE_ENUM(name, fmt_char) _##name,
typedef enum {
  TYPES_LIST(GENERATE_ENUM) TYPES_COUNT,
} types;
#undef GENERATE_ENUM

#define NOT_SPECIFIED -1  // MUST BE < 0!!!!
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#endif
