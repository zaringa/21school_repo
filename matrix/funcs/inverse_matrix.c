#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->matrix == NULL) {
    return INCORRECT_MATRIX;
  }

  if (A->rows <= 0 || A->columns <= 0) {
    return INCORRECT_MATRIX;
  }

  if (A->rows != A->columns) {
    return CALCULATION_ERROR;
  }

  double det = 0.0;
  int det_status = s21_determinant(A, &det);
  if (det_status != OK) {
    return det_status;
  }

  if (fabs(det) < 1e-12) {
    return CALCULATION_ERROR;
  }

  if (A->rows == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = 1.0 / A->matrix[0][0];
    return OK;
  }

  matrix_t comps;
  int comps_status = s21_calc_complements(A, &comps);
  if (comps_status != OK) {
    return comps_status;
  }
  matrix_t adjugate;
  int transpose_status = s21_transpose(&comps, &adjugate);
  if (transpose_status != OK) {
    s21_remove_matrix(&comps);
    return transpose_status;
  }

  int mult_status = s21_mult_number(&adjugate, 1.0 / det, result);

  s21_remove_matrix(&comps);
  s21_remove_matrix(&adjugate);

  return mult_status;
}