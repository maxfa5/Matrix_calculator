#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || !result) return INCORRECT_MATRIX;
  int code = OK, i = 0;

  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (!result->matrix) {
    free(result->matrix);
    result->matrix = NULL;
    code = CALCULATION_ERROR;
  } else {
    for (; i < rows && !code; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
    result->rows = rows;
    result->columns = columns;
  }
  return code;
}

void s21_copy_matrix(matrix_t *A, matrix_t *B) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      B->matrix[i][j] = A->matrix[i][j];
    }
  }
}