#ifndef SPRINTF_H
#define SPRINTF_H

__attribute__((format(printf, 2, 3))) void s21_sprintf(char *buf,
                                                       const char *format, ...);
#endif
