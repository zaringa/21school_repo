#include "test.h"

START_TEST(test_s21_determinant_1x1) {
  double result;
  int return_code;

  double values[] = {5.0};

  matrix_t A = create_matrix(1, 1, values);

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_double_eq_tol(result, 5.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_2x2) {
  double result;
  int return_code;

  double values[] = {1.0, 2.0, 3.0, 4.0};

  matrix_t A = create_matrix(2, 2, values);

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_double_eq_tol(result, -2.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_3x3) {
  double result;
  int return_code;

  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

  matrix_t A = create_matrix(3, 3, values);

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_3x3_non_zero) {
  double result;
  int return_code;

  double values[] = {2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0, -3.0};

  matrix_t A = create_matrix(3, 3, values);

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_double_eq_tol(result, -1.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_4x4) {
  double result;
  int return_code;

  double values[] = {1.0, 0.0, 2.0, -1.0, 3.0, 0.0, 0.0, 5.0,
                     2.0, 1.0, 4.0, -3.0, 1.0, 0.0, 5.0, 0.0};

  matrix_t A = create_matrix(4, 4, values);

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_double_eq_tol(result, 30.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_null_pointers) {
  double result;
  int return_code;

  double values[] = {1.0, 2.0, 3.0, 4.0};
  matrix_t A = create_matrix(2, 2, values);

  return_code = s21_determinant(NULL, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_determinant(&A, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_determinant(NULL, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_invalid_matrix) {
  double result;
  int return_code;

  matrix_t A = {NULL, 2, -1};

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  matrix_t B = {NULL, 2, 2};

  return_code = s21_determinant(&B, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_determinant_non_square) {
  double result;
  int return_code;

  double values[] = {1.0, 2.0, 3.0, 4.0};

  matrix_t A = create_matrix(2, 2, values);
  A.columns = 3;

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_negative_values) {
  double result;
  int return_code;

  double values[] = {-1.0, 2.0, -3.0, 4.0};

  matrix_t A = create_matrix(2, 2, values);

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_double_eq_tol(result, 2.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_zero_matrix) {
  double result;
  int return_code;

  double values[] = {0.0, 0.0, 0.0, 0.0};

  matrix_t A = create_matrix(2, 2, values);

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_identity_matrix) {
  double result;
  int return_code;

  double values[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

  matrix_t A = create_matrix(3, 3, values);

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_double_eq_tol(result, 1.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_large_matrix) {
  double result;
  int return_code;

  double values[] = {1.0,  2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,  9.0,
                     10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                     19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0};

  matrix_t A = create_matrix(5, 5, values);

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_triangular_matrix) {
  double result;
  int return_code;

  double values[] = {2.0, 3.0, 1.0, 0.0, 4.0, 5.0, 0.0, 0.0, 6.0};

  matrix_t A = create_matrix(3, 3, values);

  return_code = s21_determinant(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_double_eq_tol(result, 48.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

TCase *s21_determinant_tcase(void) {
  TCase *tc = tcase_create("s21_determinant");

  tcase_add_test(tc, test_s21_determinant_1x1);
  tcase_add_test(tc, test_s21_determinant_2x2);
  tcase_add_test(tc, test_s21_determinant_3x3);
  tcase_add_test(tc, test_s21_determinant_3x3_non_zero);
  tcase_add_test(tc, test_s21_determinant_4x4);
  tcase_add_test(tc, test_s21_determinant_null_pointers);
  tcase_add_test(tc, test_s21_determinant_invalid_matrix);
  tcase_add_test(tc, test_s21_determinant_non_square);
  tcase_add_test(tc, test_s21_determinant_negative_values);
  tcase_add_test(tc, test_s21_determinant_zero_matrix);
  tcase_add_test(tc, test_s21_determinant_identity_matrix);
  tcase_add_test(tc, test_s21_determinant_large_matrix);
  tcase_add_test(tc, test_s21_determinant_triangular_matrix);

  return tc;
}