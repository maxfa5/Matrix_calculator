#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = OK;
  if (is_valid(A) == INCORRECT_MATRIX || is_valid(B) == INCORRECT_MATRIX) {
    return INCORRECT_MATRIX;
  }

  if ((A->rows != B->columns || A->columns != B->rows))
    code = CALCULATION_ERROR;
  if (!code) code = s21_create_matrix(A->rows, B->columns, result);
  if (!code)
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < B->rows; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  return code;
}
