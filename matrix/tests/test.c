#include "test.h"

matrix_t create_matrix(int rows, int columns, double values[]) {
  matrix_t mat;
  s21_create_matrix(rows, columns, &mat);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      mat.matrix[i][j] = values[i * columns + j];
    }
  }

  return mat;
}

int is_matrix_valid(matrix_t *mat, int expected_rows, int expected_columns) {
  if (mat == NULL || mat->matrix == NULL) {
    return 0;
  }
  if (mat->rows != expected_rows || mat->columns != expected_columns) {
    return 0;
  }

  for (int i = 0; i < expected_rows; i++) {
    if (mat->matrix[i] == NULL) {
      return 0;
    }
    for (int j = 0; j < expected_columns; j++) {
      if (fabs(mat->matrix[i][j]) > 1e-10) {
        return 0;
      }
    }
  }

  return 1;
}
matrix_t create_test_matrix(int rows, int columns) {
  matrix_t mat;
  s21_create_matrix(rows, columns, &mat);

  // Заполняем матрицу тестовыми значениями
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      mat.matrix[i][j] = i * columns + j + 1;
    }
  }

  return mat;
}
int is_matrix_cleared(matrix_t *A) {
  return (A->matrix == NULL && A->rows == 0 && A->columns == 0);
}
Suite *s21_decimal_suite(void) {
  Suite *s = suite_create("s21_decimal");

  suite_add_tcase(s, (TCase *)(s21_mult_matrix_tcase()));
  suite_add_tcase(s, (TCase *)(s21_sum_matrix_tcase()));
  suite_add_tcase(s, (TCase *)(s21_sub_matrix_tcase()));
  suite_add_tcase(s, (TCase *)(s21_mult_number_tcase()));
  suite_add_tcase(s, (TCase *)(s21_remove_matrix_tcase()));
  suite_add_tcase(s, (TCase *)(s21_eq_matrix_tcase()));

  suite_add_tcase(s, (TCase *)(s21_transpose_tcase()));
  suite_add_tcase(s, (TCase *)(s21_inverse_matrix_tcase()));
  suite_add_tcase(s, (TCase *)(s21_calc_complements_tcase()));
  suite_add_tcase(s, (TCase *)(s21_determinant_tcase()));

  return s;
}

int main() {
  Suite *s = s21_decimal_suite();
  SRunner *srunner = srunner_create(s);

  srunner_run_all(srunner, CK_VERBOSE);
  srunner_free(srunner);

  printf("\nAll tests passed\n");

  return 0;
}
