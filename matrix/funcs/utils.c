#include "../s21_matrix.h"

double calculate_minor(matrix_t *A, int excluded_row, int excluded_col) {
  int minor_size = A->rows - 1;
  double minor = 0.0;

  if (minor_size == 0) {
    return 1.0;
  }

  matrix_t minor_mat;
  s21_create_matrix(minor_size, minor_size, &minor_mat);

  int minor_i = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == excluded_row) continue;

    int minor_j = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == excluded_col) continue;

      minor_mat.matrix[minor_i][minor_j] = A->matrix[i][j];
      minor_j++;
    }
    minor_i++;
  }

  s21_determinant(&minor_mat, &minor);

  s21_remove_matrix(&minor_mat);
  return minor;
}
