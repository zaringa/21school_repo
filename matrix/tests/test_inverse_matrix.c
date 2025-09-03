#include "test.h"

START_TEST(test_s21_inverse_matrix_2x2) {
  matrix_t result;
  int return_code;

  // Матрица 2x2
  double values[] = {2.0, 5.0, 1.0, 3.0};
  double expected[] = {3.0, -5.0, -1.0, 2.0};  // (1/det) * adjoint

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_inverse_matrix_3x3) {
  matrix_t result;
  int return_code;

  // Матрица 3x3
  double values[] = {2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0, -3.0};
  double expected[] = {1.0, -1.0, 1.0, -38.0, 41.0, -34.0, 27.0, -29.0, 24.0};

  matrix_t A = create_matrix(3, 3, values);
  matrix_t expected_mat = create_matrix(3, 3, expected);

  return_code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_inverse_matrix_1x1) {
  matrix_t result;
  int return_code;

  // Матрица 1x1
  double values[] = {5.0};
  double expected[] = {0.2};  // 1/5 = 0.2

  matrix_t A = create_matrix(1, 1, values);
  matrix_t expected_mat = create_matrix(1, 1, expected);

  return_code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_inverse_matrix_singular) {
  matrix_t result;
  int return_code;

  // Вырожденная матрица (определитель = 0)
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

  matrix_t A = create_matrix(3, 3, values);

  return_code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(return_code, CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_null_pointers) {
  matrix_t result;
  int return_code;

  double values[] = {1.0, 2.0, 3.0, 4.0};
  matrix_t A = create_matrix(2, 2, values);

  // Test NULL pointers
  return_code = s21_inverse_matrix(NULL, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_inverse_matrix(NULL, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_invalid_matrix) {
  matrix_t result;
  int return_code;

  // Invalid matrices
  matrix_t A = {NULL, 2, -1};  // Invalid columns

  return_code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  // Matrix with NULL data
  matrix_t B = {NULL, 2, 2};

  return_code = s21_inverse_matrix(&B, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_inverse_matrix_non_square) {
  matrix_t result;
  int return_code;

  // Не квадратная матрица
  double values[] = {1.0, 2.0, 3.0, 4.0};

  matrix_t A = create_matrix(2, 2, values);
  A.columns = 3;  // Делаем не квадратной

  return_code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(return_code, CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_identity) {
  matrix_t result;
  int return_code;

  // Обратная к единичной матрице - сама себя
  double values[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

  matrix_t A = create_matrix(3, 3, values);
  matrix_t expected_mat = create_matrix(3, 3, values);

  return_code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_inverse_matrix_product_identity) {
  matrix_t result, product;
  int return_code;

  // Проверка что A * A^(-1) = I
  double values[] = {4.0, 7.0, 2.0, 6.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t identity = create_matrix(2, 2, (double[]){1.0, 0.0, 0.0, 1.0});

  return_code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(return_code, OK);

  // Умножаем исходную матрицу на обратную
  return_code = s21_mult_matrix(&A, &result, &product);
  ck_assert_int_eq(return_code, OK);

  // Должны получить единичную матрицу
  ck_assert_int_eq(s21_eq_matrix(&product, &identity), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&product);
  s21_remove_matrix(&identity);
}
END_TEST

START_TEST(test_s21_inverse_matrix_negative_determinant) {
  matrix_t result;
  int return_code;

  // Матрица с отрицательным определителем
  double values[] = {1.0, 2.0, 3.0, 4.0};      // det = 1*4 - 2*3 = -2
  double expected[] = {-2.0, 1.0, 1.5, -0.5};  // (1/-2) * [4, -2; -3, 1]

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_inverse_matrix_zero_element) {
  matrix_t result;
  int return_code;

  // Матрица с нулевым элементом (но обратимая)
  double values[] = {0.0, 1.0, 1.0, 1.0};  // det = -1
  double expected[] = {-1.0, 1.0, 1.0, 0.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

TCase *s21_inverse_matrix_tcase(void) {
  TCase *tc = tcase_create("s21_inverse_matrix");

  tcase_add_test(tc, test_s21_inverse_matrix_2x2);
  tcase_add_test(tc, test_s21_inverse_matrix_3x3);
  tcase_add_test(tc, test_s21_inverse_matrix_1x1);
  tcase_add_test(tc, test_s21_inverse_matrix_singular);
  tcase_add_test(tc, test_s21_inverse_matrix_null_pointers);
  tcase_add_test(tc, test_s21_inverse_matrix_invalid_matrix);
  tcase_add_test(tc, test_s21_inverse_matrix_non_square);
  tcase_add_test(tc, test_s21_inverse_matrix_identity);
  tcase_add_test(tc, test_s21_inverse_matrix_product_identity);
  tcase_add_test(tc, test_s21_inverse_matrix_negative_determinant);
  tcase_add_test(tc, test_s21_inverse_matrix_zero_element);

  return tc;
}