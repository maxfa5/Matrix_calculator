#include "s21_matrix.h"

void set(double *nums, matrix_t *A) {
  int count = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = nums[count++];
    }
  }
}

int is_valid(matrix_t *A) { return (A && A->matrix) ? OK : INCORRECT_MATRIX; }

int is_valid_x_y(matrix_t *A) {
  return (A->rows >= 1 && A->columns >= 1) ? OK : INCORRECT_MATRIX;
}

// void output(matrix_t *A) {
//   int i = 0, j = 0;
//   for (; i < A->rows; i++) {
//     for (j = 0; j < A->columns; j++) {
//       printf("%lf ", A->matrix[i][j]);
//     }
//     printf("\n");
//   }
// }
