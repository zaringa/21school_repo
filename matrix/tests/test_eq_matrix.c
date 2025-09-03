#include "test.h"

START_TEST(test_s21_eq_matrix_identical) {
  double values[] = {1.0, 2.0, 3.0, 4.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t B = create_matrix(2, 2, values);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_different_values) {
  // Matrices with different values
  double valuesA[] = {1.0, 2.0, 3.0, 4.0};
  double valuesB[] = {5.0, 6.0, 7.0, 8.0};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_different_sizes) {
  // Matrices with different sizes
  double valuesA[] = {1.0, 2.0, 3.0, 4.0};
  double valuesB[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 3, valuesB);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_null_pointers) {
  double values[] = {1.0, 2.0, 3.0, 4.0};
  matrix_t A = create_matrix(2, 2, values);
  matrix_t B = create_matrix(2, 2, values);

  // Test NULL pointers
  int result1 = s21_eq_matrix(NULL, &B);
  ck_assert_int_eq(result1, FAILURE);

  int result2 = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(result2, FAILURE);

  int result3 = s21_eq_matrix(NULL, NULL);
  ck_assert_int_eq(result3, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_null_data) {
  // Matrices with NULL data pointers
  matrix_t A = {NULL, 2, 2};
  matrix_t B = {NULL, 2, 2};

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(test_s21_eq_matrix_invalid_dimensions) {
  // Matrices with invalid dimensions
  matrix_t A = {NULL, -1, 2};
  matrix_t B = {NULL, 2, -1};

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(test_s21_eq_matrix_within_epsilon) {
  // Matrices equal within epsilon precision
  double valuesA[] = {1.00000001, 2.00000002, 3.00000003, 4.00000004};
  double valuesB[] = {1.00000002, 2.00000001, 3.00000004, 4.00000003};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_beyond_epsilon) {
  // Matrices different beyond epsilon precision
  double valuesA[] = {1.0, 2.0, 3.0, 4.0};
  double valuesB[] = {1.000001, 2.000001, 3.000001, 4.000001};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_rectangular) {
  // Rectangular matrices comparison
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  matrix_t A = create_matrix(2, 3, values);
  matrix_t B = create_matrix(2, 3, values);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_single_element) {
  // Single element matrices
  double valuesA[] = {42.0};
  double valuesB[] = {42.0};

  matrix_t A = create_matrix(1, 1, valuesA);
  matrix_t B = create_matrix(1, 1, valuesB);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_large_matrices) {
  // Large matrices comparison
  const int size = 10;
  double valuesA[size * size];
  double valuesB[size * size];

  for (int i = 0; i < size * size; i++) {
    valuesA[i] = i + 1;
    valuesB[i] = i + 1;
  }

  matrix_t A = create_matrix(size, size, valuesA);
  matrix_t B = create_matrix(size, size, valuesB);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_one_different_element) {
  // Matrices with only one different element
  double valuesA[] = {1.0, 2.0, 3.0, 4.0};
  double valuesB[] = {1.0, 2.0, 3.5, 4.0};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_negative_values) {
  // Matrices with negative values
  double valuesA[] = {-1.0, -2.0, -3.0, -4.0};
  double valuesB[] = {-1.0, -2.0, -3.0, -4.0};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_mixed_signs) {
  // Matrices with mixed positive and negative values
  double valuesA[] = {1.0, -2.0, 3.0, -4.0};
  double valuesB[] = {1.0, -2.0, 3.0, -4.0};

  matrix_t A = create_matrix(2, 2, valuesA);
  matrix_t B = create_matrix(2, 2, valuesB);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

TCase *s21_eq_matrix_tcase(void) {
  TCase *tc = tcase_create("s21_eq_matrix");

  tcase_add_test(tc, test_s21_eq_matrix_identical);
  tcase_add_test(tc, test_s21_eq_matrix_different_values);
  tcase_add_test(tc, test_s21_eq_matrix_different_sizes);
  tcase_add_test(tc, test_s21_eq_matrix_null_pointers);
  tcase_add_test(tc, test_s21_eq_matrix_null_data);
  tcase_add_test(tc, test_s21_eq_matrix_invalid_dimensions);
  tcase_add_test(tc, test_s21_eq_matrix_within_epsilon);
  tcase_add_test(tc, test_s21_eq_matrix_beyond_epsilon);
  tcase_add_test(tc, test_s21_eq_matrix_rectangular);
  tcase_add_test(tc, test_s21_eq_matrix_single_element);
  tcase_add_test(tc, test_s21_eq_matrix_large_matrices);
  tcase_add_test(tc, test_s21_eq_matrix_one_different_element);
  tcase_add_test(tc, test_s21_eq_matrix_negative_values);
  tcase_add_test(tc, test_s21_eq_matrix_mixed_signs);

  return tc;
}