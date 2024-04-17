#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (is_valid(A) == INCORRECT_MATRIX || !result ||
      (is_valid_x_y(A) == INCORRECT_MATRIX)) {
    return INCORRECT_MATRIX;
  }
  if (A->rows != A->columns) {
    return CALCULATION_ERROR;
  }

  int code = OK;
  double deter = 0;
  if (A->rows == A->columns && A->rows == 1) {
    code = s21_create_matrix(1, 1, result);
    if (!code) result->matrix[0][0] = 1 / A->matrix[0][0];
  } else {
    matrix_t B = {0};
    s21_create_matrix(A->rows, A->columns, &B);
    s21_copy_matrix(A, &B);
    s21_determinant(A, &deter);
    if (fabs(deter) < ACCURACY)
      code = CALCULATION_ERROR;
    else {
      matrix_t tmp = {0};
      matrix_t tmp2 = {0};
      s21_calc_complements(&B, &tmp);
      s21_transpose(&tmp, &tmp2);
      s21_mult_number(&tmp2, 1. / deter, result);
      s21_remove_matrix(&tmp);
      s21_remove_matrix(&tmp2);
    }
    s21_remove_matrix(&B);
  }
  return code;
}