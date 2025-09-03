#include "test.h"

START_TEST(test_s21_sub_matrix_basic) {
  matrix_t result;
  int return_code;

  // Basic 2x2 subtraction
  double valuesA[] = {10.0, 8.0, 6.0, 4.0};
  double valuesB[] = {5.0, 3.0, 2.0, 1.0};
  double expected[] = {5.0, 5.0, 4.0, 3.0};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_sub_matrix_different_sizes_error) {
  matrix_t result;
  int return_code;

  // 2x2 - 3x3 = size mismatch error
  double valuesA[] = {10.0, 8.0, 6.0, 4.0};
  double valuesB[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(3, 3, valuesB);

  return_code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_sub_matrix_null_pointers) {
  matrix_t result;
  int return_code;

  double values[] = {10.0, 8.0, 6.0, 4.0};
  matrix_t A = create_matrix(2, 2, values);
  matrix_t B = create_matrix(2, 2, values);

  // Test NULL pointers
  return_code = s21_sub_matrix(NULL, &B, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_sub_matrix(&A, NULL, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_sub_matrix_invalid_matrices) {
  matrix_t result;
  int return_code;

  // Invalid matrices
  matrix_t A = {NULL, 2, -1};  // Invalid columns
  matrix_t B = {NULL, -1, 2};  // Invalid rows

  return_code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  // Matrices with NULL data
  matrix_t C = {NULL, 2, 2};
  matrix_t D = {NULL, 2, 2};

  return_code = s21_sub_matrix(&C, &D, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_sub_matrix_with_negative) {
  matrix_t result;
  int return_code;

  // Subtraction with negative numbers
  double valuesA[] = {5.0, -3.0, 2.0, -8.0};
  double valuesB[] = {-2.0, 7.0, -4.0, 1.0};
  double expected[] = {7.0, -10.0, 6.0, -9.0};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_sub_matrix_zero_matrices) {
  matrix_t result;
  int return_code;

  // Zero matrices subtraction
  double valuesA[] = {0.0, 0.0, 0.0, 0.0};
  double valuesB[] = {0.0, 0.0, 0.0, 0.0};
  double expected[] = {0.0, 0.0, 0.0, 0.0};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_sub_matrix_large_values) {
  matrix_t result;
  int return_code;

  // Large values subtraction
  double valuesA[] = {10e6, 8e6, 6e6, 4e6};
  double valuesB[] = {5e6, 3e6, 2e6, 1e6};
  double expected[] = {5e6, 5e6, 4e6, 3e6};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_sub_matrix_rectangular) {
  matrix_t result;
  int return_code;

  // Rectangular matrices subtraction
  double valuesA[] = {10.0, 8.0, 6.0, 4.0, 2.0, 0.0};
  double valuesB[] = {5.0, 3.0, 1.0, 2.0, 4.0, 6.0};
  double expected[] = {5.0, 5.0, 5.0, 2.0, -2.0, -6.0};

  matrix_t A = create_matrix(2, 3, valuesA);
  matrix_t B = create_matrix(2, 3, valuesB);
  matrix_t expected_mat = create_matrix(2, 3, expected);

  return_code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_sub_matrix_identity) {
  matrix_t result;
  int return_code;

  // Matrix - Zero matrix = Same matrix
  double valuesA[] = {10.0, 8.0, 6.0, 4.0};
  double valuesB[] = {0.0, 0.0, 0.0, 0.0};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);
  matrix_t expected_mat = create_matrix(2, 2, valuesA);  // Should equal A

  return_code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_sub_matrix_negative_result) {
  matrix_t result;
  int return_code;

  // A - B where B > A (negative results)
  double valuesA[] = {5.0, 3.0, 1.0};
  double valuesB[] = {10.0, 8.0, 6.0};
  double expected[] = {-5.0, -5.0, -5.0};

  matrix_t A = create_matrix(1, 3, valuesA);
  matrix_t B = create_matrix(1, 3, valuesB);
  matrix_t expected_mat = create_matrix(1, 3, expected);

  return_code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

TCase *s21_sub_matrix_tcase(void) {
  TCase *tc = tcase_create("s21_sub_matrix");

  tcase_add_test(tc, test_s21_sub_matrix_basic);
  tcase_add_test(tc, test_s21_sub_matrix_different_sizes_error);
  tcase_add_test(tc, test_s21_sub_matrix_null_pointers);
  tcase_add_test(tc, test_s21_sub_matrix_invalid_matrices);
  tcase_add_test(tc, test_s21_sub_matrix_with_negative);
  tcase_add_test(tc, test_s21_sub_matrix_zero_matrices);
  tcase_add_test(tc, test_s21_sub_matrix_large_values);
  tcase_add_test(tc, test_s21_sub_matrix_rectangular);
  tcase_add_test(tc, test_s21_sub_matrix_identity);
  tcase_add_test(tc, test_s21_sub_matrix_negative_result);

  return tc;
}