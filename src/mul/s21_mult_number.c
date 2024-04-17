#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int code = OK;
  if (is_valid(A) == INCORRECT_MATRIX) {
    return INCORRECT_MATRIX;
  }
  code = s21_create_matrix(A->rows, A->columns, result);
  if (!code)
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  return code;
}
