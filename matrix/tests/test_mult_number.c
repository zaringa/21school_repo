#include "test.h"

START_TEST(test_s21_mult_number_basic) {
  matrix_t result;
  int return_code;

  // Basic multiplication by positive number
  double values[] = {1.0, 2.0, 3.0, 4.0};
  double expected[] = {2.0, 4.0, 6.0, 8.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_mult_number(&A, 2.0, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_mult_number_negative) {
  matrix_t result;
  int return_code;

  // Multiplication by negative number
  double values[] = {1.0, 2.0, 3.0, 4.0};
  double expected[] = {-1.0, -2.0, -3.0, -4.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_mult_number(&A, -1.0, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_mult_number_zero) {
  matrix_t result;
  int return_code;

  // Multiplication by zero
  double values[] = {1.0, 2.0, 3.0, 4.0};
  double expected[] = {0.0, 0.0, 0.0, 0.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_mult_number(&A, 0.0, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_mult_number_fraction) {
  matrix_t result;
  int return_code;

  // Multiplication by fraction
  double values[] = {4.0, 8.0, 12.0, 16.0};
  double expected[] = {2.0, 4.0, 6.0, 8.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_mult_number(&A, 0.5, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_mult_number_null_pointers) {
  matrix_t result;
  int return_code;

  double values[] = {1.0, 2.0, 3.0, 4.0};
  matrix_t A = create_matrix(2, 2, values);

  // Test NULL pointers
  return_code = s21_mult_number(NULL, 2.0, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_mult_number(&A, 2.0, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_mult_number_invalid_matrix) {
  matrix_t result;
  int return_code;

  // Invalid matrices
  matrix_t A = {NULL, 2, -1};  // Invalid columns

  return_code = s21_mult_number(&A, 2.0, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  // Matrix with NULL data
  matrix_t B = {NULL, 2, 2};

  return_code = s21_mult_number(&B, 2.0, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_mult_number_nan_inf) {
  matrix_t result;
  int return_code;

  double values[] = {1.0, 2.0, 3.0, 4.0};
  matrix_t A = create_matrix(2, 2, values);

  // Test NaN
  return_code = s21_mult_number(&A, NAN, &result);
  ck_assert_int_eq(return_code, CALCULATION_ERROR);

  // Test positive infinity
  return_code = s21_mult_number(&A, INFINITY, &result);
  ck_assert_int_eq(return_code, CALCULATION_ERROR);

  // Test negative infinity
  return_code = s21_mult_number(&A, -INFINITY, &result);
  ck_assert_int_eq(return_code, CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_mult_number_large_values) {
  matrix_t result;
  int return_code;

  // Large values multiplication
  double values[] = {1e6, 2e6, 3e6, 4e6};
  double expected[] = {5e6, 10e6, 15e6, 20e6};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_mult_number(&A, 5.0, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_mult_number_rectangular) {
  matrix_t result;
  int return_code;

  // Rectangular matrix multiplication
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double expected[] = {3.0, 6.0, 9.0, 12.0, 15.0, 18.0};

  matrix_t A = create_matrix(2, 3, values);
  matrix_t expected_mat = create_matrix(2, 3, expected);

  return_code = s21_mult_number(&A, 3.0, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_mult_number_identity) {
  matrix_t result;
  int return_code;

  // Multiplication by 1 (identity)
  double values[] = {1.0, 2.0, 3.0, 4.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, values);  // Should equal A

  return_code = s21_mult_number(&A, 1.0, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_mult_number_small_values) {
  matrix_t result;
  int return_code;

  // Multiplication by very small number
  double values[] = {1000.0, 2000.0, 3000.0, 4000.0};
  double expected[] = {1.0, 2.0, 3.0, 4.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_mult_number(&A, 0.001, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

TCase *s21_mult_number_tcase(void) {
  TCase *tc = tcase_create("s21_mult_number");

  tcase_add_test(tc, test_s21_mult_number_basic);
  tcase_add_test(tc, test_s21_mult_number_negative);
  tcase_add_test(tc, test_s21_mult_number_zero);
  tcase_add_test(tc, test_s21_mult_number_fraction);
  tcase_add_test(tc, test_s21_mult_number_null_pointers);
  tcase_add_test(tc, test_s21_mult_number_invalid_matrix);
  tcase_add_test(tc, test_s21_mult_number_nan_inf);
  tcase_add_test(tc, test_s21_mult_number_large_values);
  tcase_add_test(tc, test_s21_mult_number_rectangular);
  tcase_add_test(tc, test_s21_mult_number_identity);
  tcase_add_test(tc, test_s21_mult_number_small_values);

  return tc;
}