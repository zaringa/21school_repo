#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || result == NULL || A->matrix == NULL) {
    return INCORRECT_MATRIX;
  }

  if (A->rows <= 0 || A->columns <= 0) {
    return INCORRECT_MATRIX;
  }

  if (A->rows != A->columns) {
    return CALCULATION_ERROR;
  }

  *result = 0.0;

  if (A->rows == 1) {
    *result = A->matrix[0][0];
    return OK;
  }

  if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    return OK;
  }

  if (A->rows == 3) {
    *result = A->matrix[0][0] * A->matrix[1][1] * A->matrix[2][2] +
              A->matrix[0][1] * A->matrix[1][2] * A->matrix[2][0] +
              A->matrix[0][2] * A->matrix[1][0] * A->matrix[2][1] -
              A->matrix[0][2] * A->matrix[1][1] * A->matrix[2][0] -
              A->matrix[0][1] * A->matrix[1][0] * A->matrix[2][2] -
              A->matrix[0][0] * A->matrix[1][2] * A->matrix[2][1];
    return OK;
  }

  for (int j = 0; j < A->columns; j++) {
    double minor = calculate_minor(A, 0, j);
    double sign = (j % 2 == 0) ? 1.0 : -1.0;
    *result += sign * A->matrix[0][j] * minor;
  }

  return OK;
}
