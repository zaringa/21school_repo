#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdarg.h>

#include "defs.h"

int format_CHARACTER(char *buf, struct token *token, va_list *args);

int format_STRING(char *buf, struct token *token, va_list *args);

int format_DECIMAL_SIGNED_INTEGER(char *buf, struct token *token,
                                  va_list *args);

int format_OCTAL_UNSIGNED_INTEGER(char *buf, struct token *token,
                                  va_list *args);

int format_HEXADECIMAL_UNSIGNED_INTEGER_UPPER(char *buf, struct token *token,
                                              va_list *args);

int format_HEXADECIMAL_UNSIGNED_INTEGER_LOWER(char *buf, struct token *token,
                                              va_list *args);

int format_DECIMAL_UNSIGNED_INTEGER(char *buf, struct token *token,
                                    va_list *args);

int format_DECIMAL_FLOAT_NUMBER(char *buf, struct token *token, va_list *args);

int format_DECIMAL_EXPONENT_FLOAT_NUMBER_UPPER(char *buf, struct token *token,
                                               va_list *args);

int format_DECIMAL_EXPONENT_FLOAT_NUMBER_LOWER(char *buf, struct token *token,
                                               va_list *args);

int format_DEPENDING_FLOAT_NUMBER_UPPER(char *buf, struct token *token,
                                        va_list *args);

int format_DEPENDING_FLOAT_NUMBER_LOWER(char *buf, struct token *token,
                                        va_list *args);

int format_NUMBER_OF_CHARACTERS(char *buf, struct token *token, va_list *args);

int format_POINTER(char *buf, struct token *token, va_list *args);

int format_PERCENT_CHARACTER(char *buf, struct token *token, va_list *args);

#endif
