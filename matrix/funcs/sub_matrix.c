#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL) {
    return INCORRECT_MATRIX;
  }

  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    return INCORRECT_MATRIX;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return CALCULATION_ERROR;
  }

  int create_status = s21_create_matrix(A->rows, A->columns, result);
  if (create_status != OK) {
    return create_status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return OK;
}