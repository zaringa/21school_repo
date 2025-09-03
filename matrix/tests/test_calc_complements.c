#include "test.h"

START_TEST(test_s21_calc_complements_3x3) {
  matrix_t result;
  int return_code;

  // Матрица 3x3
  double values[] = {1.0, 2.0, 3.0, 0.0, 4.0, 2.0, 5.0, 2.0, 1.0};
  double expected[] = {0.0, 10.0, -20.0, 4.0, -14.0, 8.0, -8.0, -2.0, 4.0};

  matrix_t A = create_matrix(3, 3, values);
  matrix_t expected_mat = create_matrix(3, 3, expected);

  return_code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_calc_complements_2x2) {
  matrix_t result;
  int return_code;

  // Матрица 2x2
  double values[] = {1.0, 2.0, 3.0, 4.0};
  double expected[] = {4.0, -3.0, -2.0, 1.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_calc_complements_1x1) {
  matrix_t result;
  int return_code;

  // Матрица 1x1
  double values[] = {5.0};
  double expected[] = {1.0};

  matrix_t A = create_matrix(1, 1, values);
  matrix_t expected_mat = create_matrix(1, 1, expected);

  return_code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_calc_complements_null_pointers) {
  matrix_t result;
  int return_code;

  double values[] = {1.0, 2.0, 3.0, 4.0};
  matrix_t A = create_matrix(2, 2, values);

  // Test NULL pointers
  return_code = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_calc_complements(NULL, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_calc_complements_invalid_matrix) {
  matrix_t result;
  int return_code;

  // Invalid matrices
  matrix_t A = {NULL, 2, -1};  // Invalid columns

  return_code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  // Matrix with NULL data
  matrix_t B = {NULL, 2, 2};

  return_code = s21_calc_complements(&B, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_calc_complements_non_square) {
  matrix_t result;
  int return_code;

  // Не квадратная матрица
  double values[] = {1.0, 2.0, 3.0, 4.0};

  matrix_t A = create_matrix(2, 2, values);
  A.columns = 3;  // Делаем не квадратной

  return_code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(return_code, CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_calc_complements_negative_values) {
  matrix_t result;
  int return_code;

  // Матрица с отрицательными значениями
  double values[] = {-1.0, 2.0, -3.0, 4.0};
  double expected[] = {4.0, 3.0, -2.0, -1.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_calc_complements_zero_matrix) {
  matrix_t result;
  int return_code;

  // Нулевая матрица
  double values[] = {0.0, 0.0, 0.0, 0.0};
  double expected[] = {0.0, 0.0, 0.0, 0.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_calc_complements_identity_matrix) {
  matrix_t result;
  int return_code;

  // Единичная матрица
  double values[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  double expected[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

  matrix_t A = create_matrix(3, 3, values);
  matrix_t expected_mat = create_matrix(3, 3, expected);

  return_code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_calc_complements_large_matrix) {
  matrix_t result;
  int return_code;

  // Большая матрица 5x5
  double values[] = {1.0,  2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,  9.0,
                     10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                     19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0};

  matrix_t A = create_matrix(5, 5, values);

  return_code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(return_code, OK);

  // Проверяем размеры результата
  ck_assert_int_eq(result.rows, 5);
  ck_assert_int_eq(result.columns, 5);

  // Для вырожденной матрицы все дополнения должны быть 0
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

TCase *s21_calc_complements_tcase(void) {
  TCase *tc = tcase_create("s21_calc_complements");

  tcase_add_test(tc, test_s21_calc_complements_3x3);
  tcase_add_test(tc, test_s21_calc_complements_2x2);
  tcase_add_test(tc, test_s21_calc_complements_1x1);
  tcase_add_test(tc, test_s21_calc_complements_null_pointers);
  tcase_add_test(tc, test_s21_calc_complements_invalid_matrix);
  tcase_add_test(tc, test_s21_calc_complements_non_square);
  tcase_add_test(tc, test_s21_calc_complements_negative_values);
  tcase_add_test(tc, test_s21_calc_complements_zero_matrix);
  tcase_add_test(tc, test_s21_calc_complements_identity_matrix);
  tcase_add_test(tc, test_s21_calc_complements_large_matrix);

  return tc;
}