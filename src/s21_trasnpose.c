#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (is_valid(A) == INCORRECT_MATRIX || is_valid_x_y(A) == INCORRECT_MATRIX) {
    return INCORRECT_MATRIX;
  }
  int code = OK;
  code = s21_create_matrix(A->columns, A->rows, result);
  if (!code)
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  return code;
}