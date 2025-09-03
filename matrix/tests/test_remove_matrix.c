#include "test.h"

START_TEST(test_s21_remove_matrix_normal) {
  // Создаем и заполняем матрицу
  matrix_t A = create_test_matrix(3, 3);

  // Проверяем, что матрица создана корректно
  ck_assert_ptr_nonnull(A.matrix);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);

  // Вызываем функцию удаления
  s21_remove_matrix(&A);

  // Проверяем, что память освобождена и поля обнулены
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_s21_remove_matrix_null_matrix_pointer) {
  // Тестирование с NULL указателем на структуру матрицы
  s21_remove_matrix(NULL);
  // Не должно быть segmentation fault
}
END_TEST

START_TEST(test_s21_remove_matrix_zero_rows) {
  // Матрица с нулевым количеством строк
  matrix_t A;
  A.rows = 0;
  A.columns = 3;
  A.matrix = (double **)malloc(sizeof(double *));

  s21_remove_matrix(&A);

  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(test_s21_remove_matrix_zero_columns) {
  // Матрица с нулевым количеством столбцов
  matrix_t A;
  A.rows = 3;
  A.columns = 0;
  A.matrix = (double **)malloc(3 * sizeof(double *));
  for (int i = 0; i < 3; i++) {
    A.matrix[i] = NULL;
  }

  s21_remove_matrix(&A);

  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(test_s21_remove_matrix_already_cleared) {
  // Попытка удалить уже очищенную матрицу
  matrix_t A = {NULL, 0, 0};

  s21_remove_matrix(&A);

  // Должно остаться в корректном состоянии
  ck_assert_int_eq(is_matrix_cleared(&A), 1);
}
END_TEST

START_TEST(test_s21_remove_matrix_partial_null_rows) {
  // Матрица с некоторыми NULL строками
  matrix_t A;
  A.rows = 3;
  A.columns = 2;
  A.matrix = (double **)malloc(3 * sizeof(double *));

  A.matrix[0] = (double *)malloc(2 * sizeof(double));
  A.matrix[1] = NULL;  // Вторая строка NULL
  A.matrix[2] = (double *)malloc(2 * sizeof(double));

  // Заполняем значениями
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;

  s21_remove_matrix(&A);

  ck_assert_int_eq(is_matrix_cleared(&A), 1);
}
END_TEST

START_TEST(test_s21_remove_matrix_double_free) {
  // Двойной вызов remove на той же матрице
  matrix_t A = create_test_matrix(2, 2);

  // Первый вызов
  s21_remove_matrix(&A);
  ck_assert_int_eq(is_matrix_cleared(&A), 1);

  // Второй вызов - не должно быть ошибки
  s21_remove_matrix(&A);
  ck_assert_int_eq(is_matrix_cleared(&A), 1);
}
END_TEST

START_TEST(test_s21_remove_matrix_large_matrix) {
  // Большая матрица
  matrix_t A = create_test_matrix(100, 100);

  ck_assert_ptr_nonnull(A.matrix);
  ck_assert_int_eq(A.rows, 100);
  ck_assert_int_eq(A.columns, 100);

  s21_remove_matrix(&A);

  ck_assert_int_eq(is_matrix_cleared(&A), 1);
}
END_TEST

START_TEST(test_s21_remove_matrix_single_element) {
  // Матрица 1x1
  matrix_t A = create_test_matrix(1, 1);

  ck_assert_ptr_nonnull(A.matrix);
  ck_assert_int_eq(A.rows, 1);
  ck_assert_int_eq(A.columns, 1);
  ck_assert_double_eq_tol(A.matrix[0][0], 1.0, 1e-6);

  s21_remove_matrix(&A);

  ck_assert_int_eq(is_matrix_cleared(&A), 1);
}
END_TEST

START_TEST(test_s21_remove_matrix_after_operations) {
  // Удаление после нескольких операций
  matrix_t A = create_test_matrix(2, 2);
  matrix_t B = create_test_matrix(2, 2);
  matrix_t result;

  // Выполняем какую-то операцию
  s21_sum_matrix(&A, &B, &result);

  // Удаляем все матрицы
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);

  // Проверяем, что все очищено
  ck_assert_int_eq(is_matrix_cleared(&A), 1);
  ck_assert_int_eq(is_matrix_cleared(&B), 1);
  ck_assert_int_eq(is_matrix_cleared(&result), 1);
}
END_TEST

TCase *s21_remove_matrix_tcase(void) {
  TCase *tc = tcase_create("s21_remove_matrix");

  tcase_add_test(tc, test_s21_remove_matrix_normal);
  tcase_add_test(tc, test_s21_remove_matrix_null_matrix_pointer);
  tcase_add_test(tc, test_s21_remove_matrix_zero_rows);
  tcase_add_test(tc, test_s21_remove_matrix_zero_columns);
  tcase_add_test(tc, test_s21_remove_matrix_already_cleared);
  tcase_add_test(tc, test_s21_remove_matrix_partial_null_rows);
  tcase_add_test(tc, test_s21_remove_matrix_double_free);
  tcase_add_test(tc, test_s21_remove_matrix_large_matrix);
  tcase_add_test(tc, test_s21_remove_matrix_single_element);
  tcase_add_test(tc, test_s21_remove_matrix_after_operations);

  return tc;
}