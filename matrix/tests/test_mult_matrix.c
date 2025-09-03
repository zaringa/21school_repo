#include "test.h"

START_TEST(test_s21_mult_matrix_basic) {
  matrix_t result;
  int return_code;

  // Basic 2x2 multiplication
  double valuesA[] = {1.0, 2.0, 3.0, 4.0};
  double valuesB[] = {5.0, 6.0, 7.0, 8.0};
  double expected[] = {19.0, 22.0, 43.0, 50.0};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_mult_matrix_different_sizes) {
  matrix_t result;
  int return_code;

  // 2x3 * 3x2 = 2x2
  double valuesA[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double valuesB[] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
  double expected[] = {58.0, 64.0, 139.0, 154.0};

  matrix_t A = create_matrix(2, 3, valuesA);
  matrix_t B = create_matrix(3, 2, valuesB);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_mult_matrix_incompatible_sizes) {
  matrix_t result;
  int return_code;

  // 2x3 * 2x3 = incompatible
  double valuesA[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double valuesB[] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

  matrix_t A = create_matrix(2, 3, valuesA);
  matrix_t B = create_matrix(2, 3, valuesB);

  return_code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_matrix_null_pointers) {
  matrix_t result;
  int return_code;

  double values[] = {1.0, 2.0, 3.0, 4.0};
  matrix_t A = create_matrix(2, 2, values);
  matrix_t B = create_matrix(2, 2, values);

  // Test NULL pointers
  return_code = s21_mult_matrix(NULL, &B, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_mult_matrix(&A, NULL, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_mult_matrix(&A, &B, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_matrix_invalid_matrices) {
  matrix_t result;
  int return_code;

  // Invalid matrices
  matrix_t A = {NULL, 2, -1};  // Invalid columns
  matrix_t B = {NULL, -1, 2};  // Invalid rows

  return_code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  // Matrices with NULL data
  matrix_t C = {NULL, 2, 2};
  matrix_t D = {NULL, 2, 2};

  return_code = s21_mult_matrix(&C, &D, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_mult_matrix_with_zero) {
  matrix_t result;
  int return_code;

  // Multiplication with zero matrix
  double valuesA[] = {1.0, 0.0, 0.0, 1.0};  // Identity matrix
  double valuesB[] = {5.0, 6.0, 7.0, 8.0};
  double expected[] = {5.0, 6.0, 7.0, 8.0};  // Should equal B

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_mult_matrix_large_values) {
  matrix_t result;
  int return_code;

  // Large values multiplication
  double valuesA[] = {1e6, 2e6, 3e6, 4e6};
  double valuesB[] = {5e6, 6e6, 7e6, 8e6};
  double expected[] = {1e6 * 5e6 + 2e6 * 7e6, 1e6 * 6e6 + 2e6 * 8e6,
                       3e6 * 5e6 + 4e6 * 7e6, 3e6 * 6e6 + 4e6 * 8e6};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_mult_matrix_vector_multiplication) {
  matrix_t result;
  int return_code;

  // Vector multiplication: 1x3 * 3x1 = 1x1 (scalar)
  double valuesA[] = {1.0, 2.0, 3.0};
  double valuesB[] = {4.0, 5.0, 6.0};
  double expected[] = {32.0};  // 1*4 + 2*5 + 3*6

  matrix_t A = create_matrix(1, 3, valuesA);
  matrix_t B = create_matrix(3, 1, valuesB);
  matrix_t expected_mat = create_matrix(1, 1, expected);

  return_code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

TCase *s21_mult_matrix_tcase(void) {
  TCase *tc = tcase_create("s21_mult_matrix");

  tcase_add_test(tc, test_s21_mult_matrix_basic);
  tcase_add_test(tc, test_s21_mult_matrix_different_sizes);
  tcase_add_test(tc, test_s21_mult_matrix_incompatible_sizes);
  tcase_add_test(tc, test_s21_mult_matrix_null_pointers);
  tcase_add_test(tc, test_s21_mult_matrix_invalid_matrices);
  tcase_add_test(tc, test_s21_mult_matrix_with_zero);
  tcase_add_test(tc, test_s21_mult_matrix_large_values);
  tcase_add_test(tc, test_s21_mult_matrix_vector_multiplication);

  return tc;
}