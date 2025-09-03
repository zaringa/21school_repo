#include "help.h"

int comprec(const void *a, const void *b) {
  struct reco *reco_a = (struct reco *)a;
  struct reco *reco_b = (struct reco *)b;
  int result = 0;
  if (reco_a->year != reco_b->year) {
    result = reco_a->year - reco_b->year;
  } else if (reco_a->month != reco_b->month) {
    result = reco_a->month - reco_b->month;
  } else if (reco_a->day != reco_b->day) {
    result = reco_a->day - reco_b->day;
  } else if (reco_a->hour != reco_b->hour) {
    result = reco_a->hour - reco_b->hour;
  } else if (reco_a->mi != reco_b->mi) {
    result = reco_a->mi - reco_b->mi;
  } else if (reco_a->se != reco_b->se) {
    result = reco_a->se - reco_b->se;
  }
  return result;
}

void print_reco(struct reco *reco) {
  printf("%d %d %d %d %d %d %d %d\n", reco->year, reco->month, reco->day,
         reco->hour, reco->mi, reco->se, reco->status, reco->code);
}

int input_reco(struct reco *new_reco) {
  int res = 0;
  if (scanf("%d", &new_reco->year) != 1) {
    printf("n/a");
    res = 1;
  }
  if (scanf("%d", &new_reco->month) != 1) {
    printf("n/a");
    res = 1;
  }
  if (scanf("%d", &new_reco->day) != 1) {
    printf("n/a");
    res = 1;
  }
  if (scanf("%d", &new_reco->hour) != 1) {
    printf("n/a");
    res = 1;
  }
  if (scanf("%d", &new_reco->mi) != 1) {
    printf("n/a");
    res = 1;
  }
  if (scanf("%d", &new_reco->se) != 1) {
    printf("n/a");
    res = 1;
  }
  if (scanf("%d", &new_reco->status) != 1) {
    printf("n/a");
    res = 1;
  }
  if (scanf("%d", &new_reco->code) != 1) {
    printf("n/a");
    res = 1;
  }
  if (new_reco->year > 2023 || new_reco->month < 0 || new_reco->month > 12 ||
      new_reco->day < 0 || new_reco->day > 31 || new_reco->hour < 0 ||
      new_reco->hour > 23 || new_reco->mi < 0 || new_reco->mi > 59 ||
      new_reco->se < 0 || new_reco->se > 59 || new_reco->status < 0 ||
      new_reco->status > 1) {
    printf("n/a");
    res = 1;
  }
  return res;
}
