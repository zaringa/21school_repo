#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdio.h>

int s21_strlen(char *st);
int s21_strcmp(char *a, char *b);
int s21_strcpy(char *a, char *b);
int s21_strcat(char *a, char *b);
char *s21_strchr(char *a, char *b);
char *s21_strstr(char *a, char *b);
char *s21_strtok(char *a, const char *b);

#endif