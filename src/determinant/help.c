#include "../s21_matrix.h"

void swap(int str1, int str2, matrix_t *A) {
  double tmp = 0;
  for (int i = 0; i < A->columns; i++) {
    tmp = A->matrix[str1][i];
    A->matrix[str1][i] = A->matrix[str2][i];
    A->matrix[str2][i] = tmp;
  }
}

void s21_sub_rows(matrix_t *A, int minuend, int subtrahend, double mul) {
  for (int i = 0; i < A->columns; i++) {
    A->matrix[minuend][i] -= A->matrix[subtrahend][i] * mul;
  }
}
// 1 - под этим эллементом нулевые обьекты
int check_null_under(matrix_t *A, int column, int row) {
  int code = 1;
  row++;
  for (; row < A->rows && code; row++) {
    if (A->matrix[row][column]) code--;
  }
  return code;
}

void to_triangle_form(matrix_t *A) {
  int column = 0, row = 0;
  for (; column < A->columns && row < A->rows; column++, row++) {
    if (!check_null_under(A, column, row)) {
      rows_to_null(A, row, column);
    }
  }
}

void rows_to_null(matrix_t *A, int start_row, int column) {
  int go_row = start_row + 1;
  double mul1 = A->matrix[go_row][column] / A->matrix[start_row][column];
  for (; go_row < A->rows; go_row++) {
    mul1 = A->matrix[go_row][column] / A->matrix[start_row][column];
    s21_sub_rows(A, go_row, start_row, mul1);
  }
}

double mul_diagonal(matrix_t *A) {
  double res = 1;
  for (int i = 0; i < A->rows; i++) res *= A->matrix[i][i];
  return res;
}

int swap_zeros(matrix_t *A, int sign, int column) {
  for (int i = 0; i < A->rows; i++)
    if (A->matrix[i][column] == 0) {
      swap(i, not_null_str(A), A);
      sign *= (-1);
      break;
    }
  return sign;
}

int not_null_str(matrix_t *A) {
  int result = 0;
  for (int i = 0; i < A->rows; i++)
    if (A->matrix[i][0] != 0) {
      result = i;
    }
  return result;
}