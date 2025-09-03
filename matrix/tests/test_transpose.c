#include "test.h"

START_TEST(test_s21_transpose_square_matrix) {
  matrix_t result;
  int return_code;

  // Квадратная матрица
  double values[] = {1.0, 2.0, 3.0, 4.0};
  double expected[] = {1.0, 3.0, 2.0, 4.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_transpose(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_transpose_rectangular_matrix) {
  matrix_t result;
  int return_code;

  // Прямоугольная матрица 2x3
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double expected[] = {1.0, 4.0, 2.0, 5.0, 3.0, 6.0};

  matrix_t A = create_matrix(2, 3, values);
  matrix_t expected_mat = create_matrix(3, 2, expected);

  return_code = s21_transpose(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_transpose_row_vector) {
  matrix_t result;
  int return_code;

  // Вектор-строка (1x3) -> вектор-столбец (3x1)
  double values[] = {1.0, 2.0, 3.0};
  double expected[] = {1.0, 2.0, 3.0};

  matrix_t A = create_matrix(1, 3, values);
  matrix_t expected_mat = create_matrix(3, 1, expected);

  return_code = s21_transpose(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_transpose_column_vector) {
  matrix_t result;
  int return_code;

  // Вектор-столбец (3x1) -> вектор-строка (1x3)
  double values[] = {1.0, 2.0, 3.0};
  double expected[] = {1.0, 2.0, 3.0};

  matrix_t A = create_matrix(3, 1, values);
  matrix_t expected_mat = create_matrix(1, 3, expected);

  return_code = s21_transpose(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_transpose_single_element) {
  matrix_t result;
  int return_code;

  // Матрица 1x1
  double values[] = {42.0};
  double expected[] = {42.0};

  matrix_t A = create_matrix(1, 1, values);
  matrix_t expected_mat = create_matrix(1, 1, expected);

  return_code = s21_transpose(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_transpose_null_pointers) {
  matrix_t result;
  int return_code;

  double values[] = {1.0, 2.0, 3.0, 4.0};
  matrix_t A = create_matrix(2, 2, values);

  // Test NULL pointers
  return_code = s21_transpose(NULL, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_transpose(&A, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  return_code = s21_transpose(NULL, NULL);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_transpose_invalid_matrix) {
  matrix_t result;
  int return_code;

  // Invalid matrices
  matrix_t A = {NULL, 2, -1};  // Invalid columns

  return_code = s21_transpose(&A, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);

  // Matrix with NULL data
  matrix_t B = {NULL, 2, 2};

  return_code = s21_transpose(&B, &result);
  ck_assert_int_eq(return_code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_transpose_double_transpose) {
  matrix_t result1, result2;
  int return_code;

  // Двойное транспонирование должно вернуть исходную матрицу
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  matrix_t A = create_matrix(2, 3, values);
  matrix_t original = create_matrix(2, 3, values);

  // Первое транспонирование
  return_code = s21_transpose(&A, &result1);
  ck_assert_int_eq(return_code, OK);

  // Второе транспонирование
  return_code = s21_transpose(&result1, &result2);
  ck_assert_int_eq(return_code, OK);

  // Результат должен совпадать с оригиналом
  ck_assert_int_eq(s21_eq_matrix(&result2, &original), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&original);
}
END_TEST

START_TEST(test_s21_transpose_large_matrix) {
  matrix_t result;
  int return_code;

  // Большая матрица
  const int rows = 10;
  const int cols = 8;
  double values[rows * cols];
  double expected[cols * rows];

  // Заполняем исходную матрицу
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      values[i * cols + j] = i * cols + j + 1;
    }
  }

  // Заполняем ожидаемую транспонированную матрицу
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      expected[j * rows + i] = values[i * cols + j];
    }
  }

  matrix_t A = create_matrix(rows, cols, values);
  matrix_t expected_mat = create_matrix(cols, rows, expected);

  return_code = s21_transpose(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_transpose_with_negative_values) {
  matrix_t result;
  int return_code;

  // Матрица с отрицательными значениями
  double values[] = {-1.0, 2.0, -3.0, 4.0, -5.0, 6.0};
  double expected[] = {-1.0, 4.0, 2.0, -5.0, -3.0, 6.0};

  matrix_t A = create_matrix(2, 3, values);
  matrix_t expected_mat = create_matrix(3, 2, expected);

  return_code = s21_transpose(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

START_TEST(test_s21_transpose_zero_matrix) {
  matrix_t result;
  int return_code;

  // Нулевая матрица
  double values[] = {0.0, 0.0, 0.0, 0.0};
  double expected[] = {0.0, 0.0, 0.0, 0.0};

  matrix_t A = create_matrix(2, 2, values);
  matrix_t expected_mat = create_matrix(2, 2, expected);

  return_code = s21_transpose(&A, &result);
  ck_assert_int_eq(return_code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected_mat), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_mat);
}
END_TEST

TCase *s21_transpose_tcase(void) {
  TCase *tc = tcase_create("s21_transpose");

  tcase_add_test(tc, test_s21_transpose_square_matrix);
  tcase_add_test(tc, test_s21_transpose_rectangular_matrix);
  tcase_add_test(tc, test_s21_transpose_row_vector);
  tcase_add_test(tc, test_s21_transpose_column_vector);
  tcase_add_test(tc, test_s21_transpose_single_element);
  tcase_add_test(tc, test_s21_transpose_null_pointers);
  tcase_add_test(tc, test_s21_transpose_invalid_matrix);
  tcase_add_test(tc, test_s21_transpose_double_transpose);
  tcase_add_test(tc, test_s21_transpose_large_matrix);
  tcase_add_test(tc, test_s21_transpose_with_negative_values);
  tcase_add_test(tc, test_s21_transpose_zero_matrix);

  return tc;
}