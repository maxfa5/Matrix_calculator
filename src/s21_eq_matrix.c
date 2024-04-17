#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int code = 1, i = 0, j = 0;
  if (is_valid(A) == INCORRECT_MATRIX || is_valid(B) == INCORRECT_MATRIX) {
    return FAILURE;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    return FAILURE;
  }
  for (; i < A->rows && code; i++) {
    for (; j < A->columns && code; j++) {
      code =
          (A->matrix[i][j] - B->matrix[i][j]) >= ACCURACY ? FAILURE : SUCCESS;
    }
  }
  return code;
}