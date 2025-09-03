#ifndef TESTS
#define TESTS

#include <check.h>
#include <limits.h>

#include "../s21_matrix.h"

TCase *s21_mult_matrix_tcase(void);
TCase *s21_sum_matrix_tcase(void);
TCase *s21_sub_matrix_tcase(void);
TCase *s21_mult_number_tcase(void);
TCase *s21_remove_matrix_tcase(void);
TCase *s21_eq_matrix_tcase(void);

TCase *s21_transpose_tcase(void);
TCase *s21_inverse_matrix_tcase(void);
TCase *s21_calc_complements_tcase(void);
TCase *s21_determinant_tcase(void);

matrix_t create_matrix(int rows, int columns, double values[]);
int is_matrix_valid(matrix_t *mat, int expected_rows, int expected_columns);
matrix_t create_test_matrix(int rows, int columns);
int is_matrix_cleared(matrix_t *A);
#endif