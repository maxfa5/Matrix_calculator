#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_valid(A) == INCORRECT_MATRIX || is_valid(B) == INCORRECT_MATRIX) {
    return INCORRECT_MATRIX;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    return CALCULATION_ERROR;
  }
  int code = OK;
  code = s21_create_matrix(A->rows, A->columns, result);
  if (!code)
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  return code;
}