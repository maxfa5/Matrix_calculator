#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  if (A->rows) {
    A->rows = 0;
  }
  if (A->columns) {
    A->columns = 0;
  }
}
