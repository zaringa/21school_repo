#include "test.h"

START_TEST(test_s21_create_matrix_normal) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(3, 4, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(is_matrix_valid(&result, 3, 4), 1);

  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_create_matrix_square) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(5, 5, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(is_matrix_valid(&result, 5, 5), 1);

  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_create_matrix_rectangular) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(2, 7, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(is_matrix_valid(&result, 2, 7), 1);

  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_create_matrix_single_element) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(1, 1, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(is_matrix_valid(&result, 1, 1), 1);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 1e-10);

  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_create_matrix_row_vector) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(1, 5, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(is_matrix_valid(&result, 1, 5), 1);

  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_create_matrix_column_vector) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(5, 1, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(is_matrix_valid(&result, 5, 1), 1);

  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_create_matrix_zero_rows) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(0, 5, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
  ck_assert_ptr_null(result.matrix);
}
END_TEST

START_TEST(test_s21_create_matrix_zero_columns) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(5, 0, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
  ck_assert_ptr_null(result.matrix);
}
END_TEST

START_TEST(test_s21_create_matrix_negative_rows) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(-3, 5, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
  ck_assert_ptr_null(result.matrix);
}
END_TEST

START_TEST(test_s21_create_matrix_negative_columns) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(5, -3, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
  ck_assert_ptr_null(result.matrix);
}
END_TEST

START_TEST(test_s21_create_matrix_null_result) {
  int return_code;

  return_code = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_create_matrix_large_matrix) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(100, 100, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(is_matrix_valid(&result, 100, 100), 1);

  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_create_matrix_memory_allocation_failure) {
  matrix_t result;
  int return_code;
  return_code = s21_create_matrix(10000, 10000, &result);
  if (return_code == OK) {
    ck_assert_int_eq(is_matrix_valid(&result, 10000, 10000), 1);
    s21_remove_matrix(&result);
  } else {
    ck_assert_int_eq(return_code, INCORRECT_MATRIX);
  }
}
END_TEST

START_TEST(test_s21_create_matrix_zero_initialization) {
  matrix_t result;
  int return_code;

  return_code = s21_create_matrix(2, 3, &result);
  ck_assert_int_eq(return_code, OK);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-10);
    }
  }

  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_create_matrix_multiple_creates) {
  matrix_t mat1, mat2, mat3;
  int return_code;

  return_code = s21_create_matrix(2, 2, &mat1);
  ck_assert_int_eq(return_code, OK);

  return_code = s21_create_matrix(3, 4, &mat2);
  ck_assert_int_eq(return_code, OK);

  return_code = s21_create_matrix(1, 5, &mat3);
  ck_assert_int_eq(return_code, OK);

  ck_assert_int_eq(is_matrix_valid(&mat1, 2, 2), 1);
  ck_assert_int_eq(is_matrix_valid(&mat2, 3, 4), 1);
  ck_assert_int_eq(is_matrix_valid(&mat3, 1, 5), 1);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&mat3);
}
END_TEST

START_TEST(test_s21_create_matrix_very_large_dimensions) {
  matrix_t result;
  int return_code;
  return_code = s21_create_matrix(INT_MAX, INT_MAX, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
  ck_assert_ptr_null(result.matrix);
}
END_TEST

TCase *s21_create_matrix_tcase(void) {
  TCase *tc = tcase_create("s21_create_matrix");

  tcase_add_test(tc, test_s21_create_matrix_normal);
  tcase_add_test(tc, test_s21_create_matrix_square);
  tcase_add_test(tc, test_s21_create_matrix_rectangular);
  tcase_add_test(tc, test_s21_create_matrix_single_element);
  tcase_add_test(tc, test_s21_create_matrix_row_vector);
  tcase_add_test(tc, test_s21_create_matrix_column_vector);
  tcase_add_test(tc, test_s21_create_matrix_zero_rows);
  tcase_add_test(tc, test_s21_create_matrix_zero_columns);
  tcase_add_test(tc, test_s21_create_matrix_negative_rows);
  tcase_add_test(tc, test_s21_create_matrix_negative_columns);
  tcase_add_test(tc, test_s21_create_matrix_null_result);
  tcase_add_test(tc, test_s21_create_matrix_large_matrix);
  tcase_add_test(tc, test_s21_create_matrix_memory_allocation_failure);
  tcase_add_test(tc, test_s21_create_matrix_zero_initialization);
  tcase_add_test(tc, test_s21_create_matrix_multiple_creates);
  tcase_add_test(tc, test_s21_create_matrix_very_large_dimensions);

  return tc;
}