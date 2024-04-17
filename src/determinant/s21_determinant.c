#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int sign = 1;
  if (A->columns == A->rows) {
    for (int i = 0; !mul_diagonal(A) && i < A->rows; i++) {
      sign = swap_zeros(A, sign, i);
    }

    if (!mul_diagonal(A)) { /*проверка на 0 на главной диагонали */
      *result = 0;
    } else {
      to_triangle_form(A);
      *result = mul_diagonal(A) * sign;
    }
  }
  return 0;
}
