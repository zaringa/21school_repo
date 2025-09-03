#ifndef HELP_H
#define HELP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct reco {
  int year;
  int month;
  int day;
  int hour;
  int mi;
  int se;
  int status;
  int code;
};
int comprec(const void *a, const void *b);
void print_reco(struct reco *reco);
int input_reco(struct reco *new_reco);

#endif