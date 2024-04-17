#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (is_valid(A) == INCORRECT_MATRIX || !result ||
      (is_valid_x_y(A) == INCORRECT_MATRIX)) {
    return INCORRECT_MATRIX;
  }
  if (A->rows != A->columns) {
    return CALCULATION_ERROR;
  }

  int code = OK, sign = 1;
  code = s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      sign = ((i + j) % 2) ? -1 : 1;
      result->matrix[i][j] = minor(A, i, j) * sign;
    }
  }
  return code;
}

double minor(matrix_t *A, int row, int column) {
  double det = 0;
  matrix_t result = {0};
  int k = 0;
  s21_create_matrix(A->rows - 1, A->columns - 1, &result);
  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;
    for (int j = 0, l = 0; j < A->columns; j++) {
      if (j == column) continue;
      result.matrix[k][l] = A->matrix[i][j];
      l++;
    }
    k++;
  }
  s21_determinant(&result, &det);

  s21_remove_matrix(&result);
  return det;
}
