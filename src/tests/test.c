#include <check.h>

#include "../s21_matrix.h"

START_TEST(test_s21_create_matrix) {
  matrix_t s21_matrix = {0};

  ck_assert_int_eq(s21_create_matrix(5, 5, &s21_matrix), 0);
  s21_remove_matrix(&s21_matrix);

  ck_assert_int_eq(s21_create_matrix(0, 0, &s21_matrix), 1);
  ck_assert_int_eq(s21_create_matrix(-1, 10, &s21_matrix), 1);
  ck_assert_int_eq(s21_create_matrix(400U, 4000000000U, &s21_matrix), 1);
  ck_assert_int_eq(s21_create_matrix(5, 5, NULL), 1);
  s21_remove_matrix(&s21_matrix);
}
END_TEST

START_TEST(test_s21_eq_matrix) {
  matrix_t s21_matrixA = {0};
  matrix_t s21_matrixB = {0};

  s21_create_matrix(5, 5, &s21_matrixA);
  s21_create_matrix(5, 5, &s21_matrixB);
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, &s21_matrixB), 1);

  s21_remove_matrix(&s21_matrixA);
  s21_remove_matrix(&s21_matrixB);

  s21_create_matrix(2, 5, &s21_matrixB);
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, &s21_matrixB), 0);

  s21_remove_matrix(&s21_matrixA);
  s21_remove_matrix(&s21_matrixB);

  s21_create_matrix(5, 1, &s21_matrixA);
  s21_create_matrix(5, 2, &s21_matrixB);
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, &s21_matrixB), 0);

  s21_remove_matrix(&s21_matrixA);
  s21_remove_matrix(&s21_matrixB);

  s21_create_matrix(5, 5, &s21_matrixA);
  s21_create_matrix(5, 5, &s21_matrixB);
  s21_matrixA.matrix[0][0] = 10;
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, &s21_matrixB), 0);

  s21_remove_matrix(&s21_matrixA);
  s21_remove_matrix(&s21_matrixB);

  s21_create_matrix(5, 5, &s21_matrixB);
  ck_assert_int_eq(s21_eq_matrix(NULL, &s21_matrixB), 0);

  s21_remove_matrix(&s21_matrixB);

  s21_create_matrix(5, 5, &s21_matrixA);
  ck_assert_int_eq(s21_eq_matrix(&s21_matrixA, NULL), 0);

  s21_remove_matrix(&s21_matrixA);
}
END_TEST
START_TEST(test_inverse_matrix_1) {
  static double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  static double res_array[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  int row = 3;
  int col = 3;
  matrix_t A;
  matrix_t result;
  matrix_t correct_result;
  s21_create_matrix(row, col, &A);
  s21_create_matrix(row, col, &correct_result);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      correct_result.matrix[i][j] = res_array[i][j];
    }

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);
  code = s21_eq_matrix(&result, &correct_result);
  ck_assert_int_eq(code, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&correct_result);
}
END_TEST

START_TEST(test_inverse_matrix_2) {
  matrix_t A;
  matrix_t *result = NULL;

  int code = s21_inverse_matrix(&A, result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_inverse_matrix_3) {
  matrix_t A;
  matrix_t result;

  A.matrix = NULL;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_inverse_matrix_4) {
  int row = 2;
  int col = 1;
  matrix_t A;
  matrix_t result;

  s21_create_matrix(row, col, &A);

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST


START_TEST(test_calc_complements_1) {
  static double array[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  static double res_array[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  int row = 3;
  int col = 3;
  matrix_t A;
  matrix_t result;
  matrix_t correct_result;
  s21_create_matrix(row, col, &A);
  s21_create_matrix(row, col, &correct_result);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      correct_result.matrix[i][j] = res_array[i][j];
    }

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);
  code = s21_eq_matrix(&result, &correct_result);
  ck_assert_int_eq(code, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&correct_result);
}
END_TEST

START_TEST(test_calc_complements_2) {
  matrix_t A;
  matrix_t *result = NULL;

  int code = s21_calc_complements(&A, result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_calc_complements_3) {
  matrix_t A;
  matrix_t result;
  A.matrix = NULL;

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_calc_complements_4) {
  int row = 2;
  int col = 1;
  matrix_t A;
  matrix_t result;

  s21_create_matrix(row, col, &A);

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_sum_matrix) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), INCORRECT_MATRIX);

  s21_create_matrix(4, 4, &A);
  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &B), INCORRECT_MATRIX);
  s21_remove_matrix(&A);

  s21_remove_matrix(&result);
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(5, 5, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  matrix_t C;
  matrix_t D;
  double A_nums[6] = {1, 2, 3, 4, 5, 6};
  double B_nums[6] = {2, 3, 4, 5, 6, 7};
  double result_nums[6] = {3, 5, 7, 9, 11, 13};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(3, 2, &C);
  set(A_nums, &A);
  set(B_nums, &B);
  set(result_nums, &C);
  int res = s21_sum_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_s21_sub_matrix) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t C;
  matrix_t D;
  matrix_t result = {};
  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), INCORRECT_MATRIX);
  s21_create_matrix(4, 4, &A);
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &B), INCORRECT_MATRIX);
  s21_remove_matrix(&A);

  s21_remove_matrix(&result);
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(5, 5, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  double A_nums[6] = {3, 5, 7, 9, 11, 13};
  double B_nums[6] = {2, 3, 4, 5, 6, 7};
  double result_nums[6] = {1, 2, 3, 4, 5, 6};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(3, 2, &C);
  set(A_nums, &A);
  set(B_nums, &B);
  set(result_nums, &C);
  int res = s21_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(multi_num_1) {
  matrix_t A;
  ck_assert_int_eq(s21_mult_number(NULL, (double)10, &A), INCORRECT_MATRIX);
}
END_TEST

START_TEST(multi_num_2) {
  matrix_t A;
  matrix_t C;
  s21_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = s21_mult_number(&A, (double)10, &C);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(multi_num_3) {
  matrix_t A;
  double number = 3.12890;
  matrix_t B;
  matrix_t C;
  double A_nums[4] = {121239.113, 2401.12392, -348901.2, 2389014};
  double result_nums[4] = {379345.0606657, 7512.876633288, -1091676.96468,
                           7474985.9046};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  set(A_nums, &A);
  set(result_nums, &B);
  int result = s21_mult_number(&A, number, &C);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(multi_num_4) {
  matrix_t A;
  double number = 3901.904;
  matrix_t B;
  matrix_t C;
  double A_nums[9] = {121239.122013, 2401.12392,   -348901.2, 2389014,
                      912039.12389,  129034.23400, 0,         1203,
                      9000000.123};
  double result_nums[9] = {473063415.139012752,
                           9368955.02794368,
                           -1361378987.8848,
                           9321703282.656,
                           3558689105.66288656,
                           503479193.781536,
                           0,
                           4693990.512,
                           35117136479.934192};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  set(A_nums, &A);
  set(result_nums, &B);
  int res = s21_mult_number(&A, number, &C);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(multi_mat_1) {
  matrix_t A;
  ck_assert_int_eq(s21_mult_matrix(NULL, &A, &A), 1);
}
END_TEST

START_TEST(multi_mat_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  int result = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(multi_mat_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[6] = {1.2, 2.4, 3.6, 4.8, 6.0, 7.2};
  double B_nums[6] = {3.5, 7.0, 10.5, 14.0, 17.5, 21.0};
  double result_nums[9] = {92.4, 117.6, 205.8, 268.8};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(2, 2, &C);
  set(A_nums, &A);
  set(B_nums, &B);
  set(result_nums, &C);
  int res = s21_mult_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(multi_mat_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[9] = {1.2, 2.4, 3.6, 4.8, 6.0, 7.2, 8.4, 9.6, 10.8};
  double B_nums[9] = {3.5, 7.0, 10.5, 14.0, 17.5, 21.0, 24.5, 28.0, 31.5};
  double result_nums[9] = {126,   151.2, 176.4, 277.2, 340.2,
                           403.2, 428.4, 529.2, 630};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &C);
  set(A_nums, &A);
  set(B_nums, &B);
  set(result_nums, &C);
  int res = s21_mult_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(multi_mat_6) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[6] = {1.2, 2.4, 3.6, 4.8, 6.0, 7.2};
  double B_nums[6] = {3.5, 7.0, 10.5, 14.0, 17.5, 21.0};
  double result_nums[9] = {37.8,  50.4,  63,  79.8, 109.2,
                           138.6, 121.8, 168, 214.2};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &C);
  set(A_nums, &A);
  set(B_nums, &B);
  set(result_nums, &C);
  int res = s21_mult_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(transpose_1) {
  matrix_t A;
  int res = s21_transpose(NULL, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(1, 1, &A);
  A.rows = 0;
  int res = s21_transpose(&A, &B);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_nums[6] = {1, 2, 3, 4, 5, 6};
  double result_nums[6] = {1, 4, 2, 5, 3, 6};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &C);
  set(A_nums, &A);
  set(result_nums, &C);
  int res = s21_transpose(&A, &B);
  ck_assert_int_eq(s21_eq_matrix(&C, &B), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(transpose_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double result_nums[9] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  set(A_nums, &A);
  set(result_nums, &C);
  int res = s21_transpose(&A, &B);
  ck_assert_int_eq(s21_eq_matrix(&C, &B), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(transpose_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_nums[6] = {1, 2, 3, 4, 5, 6};
  double result_nums[6] = {1, 3, 5, 2, 4, 6};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &C);
  set(A_nums, &A);
  set(result_nums, &C);
  int res = s21_transpose(&A, &B);
  ck_assert_int_eq(s21_eq_matrix(&C, &B), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(transpose_6) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_nums[10] = {984, 21, 4, 2, 1, 2, 3, 4, 6, 9};
  double result_nums[10] = {984, 2, 21, 3, 4, 4, 2, 6, 1, 9};
  s21_create_matrix(2, 5, &A);
  s21_create_matrix(5, 2, &C);
  set(A_nums, &A);
  set(result_nums, &C);
  int res = s21_transpose(&A, &B);
  ck_assert_int_eq(s21_eq_matrix(&C, &B), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(determinant_01) {
  double determinant = 0;
  matrix_t A = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 0.0;
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, 0.0, ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_02) {
  double determinant = 0;
  matrix_t A = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1.0;
  ck_assert_uint_eq(s21_determinant(&A, &determinant), OK);
  ck_assert_double_eq_tol(determinant, 1.0, ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_03) {
  double determinant = 0;
  matrix_t A = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = -213123.464566456;
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, -213123.464566456, ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_05) {
  double determinant = 0, arr[4] = {0, 0, 0, 0};
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  set(arr, &A);
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, 0., ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_1) {
  double determinant = 0, arr[16] = {4.,  4., 4.,  4.,  5., 6.,  7.,  8.,
                                     10., 2., 12., 13., 1., 16., 17., 4.};
  matrix_t A = {0};
  s21_create_matrix(4, 4, &A);
  set(arr, &A);
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, -1512., ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2) {
  double determinant = 0, arr[16] = {5.,  6.,  7.,  8.,  9.,  10., 11., 12.,
                                     13., 14., 14., 15., 17., 18., 19., 21.};
  matrix_t A = {0};
  s21_create_matrix(4, 4, &A);
  set(arr, &A);
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, 4., ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3) {
  double determinant = 0,
         arr[16] = {100., -19., 22., 111., 0.,  9.,  144., 1.,
                    2.,   3.,   6.,  12.,  17., 18., 19.,  21.};
  matrix_t A = {0};
  s21_create_matrix(4, 4, &A);
  set(arr, &A);
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, 2755886., ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_4) {
  double determinant = 0, arr[9] = {10.1, 2., 3., 4., 5., 6., 7., 8., 9.};
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  set(arr, &A);
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, -27.3, ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_5) {
  double determinant = 0, arr[16] = {0., 1., 2., 3.,  4.,  0.,  6.,  6.,
                                     7., 8., 9., 10., 10., 12., 13., 14.};
  matrix_t A = {0};
  s21_create_matrix(4, 4, &A);
  set(arr, &A);
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, -42., ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(determinant_6) {
  double determinant = 0,
         arr[16] = {1.7, 21.,  23.,  45., 56.,  12., -21., -67.,
                    9.,  -4.2, 4.23, 3.,  0.34, 10., 0.,   78.3};
  matrix_t A = {0};
  s21_create_matrix(4, 4, &A);
  set(arr, &A);
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, -1308183.9558, ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_7) {
  double determinant = 0,
         arr[16] = {34.2, 0.,   56.,   0., 0.1, 13.45, -21., 0.,
                    1.78, 43.0, 89.83, 0., 0.,  0.,    12.,  -29.51};
  matrix_t A = {0};
  s21_create_matrix(4, 4, &A);
  set(arr, &A);
  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, -2098267.404207, ACCURACY);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_1) {
  int res = s21_inverse_matrix(NULL, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(inverse_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(10, 9, &A);
  int res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &C);
  A.matrix[0][0] = 42.12849;
  C.matrix[0][0] = 1. / 42.12849;
  int res = s21_inverse_matrix(&A, &B);
  ck_assert_double_eq(s21_eq_matrix(&B, &C), 1);

  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_nums[9] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double result_nums[9] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  set(A_nums, &A);
  set(result_nums, &C);
  int res = s21_inverse_matrix(&A, &B);
  ck_assert_double_eq(s21_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_6) {
  matrix_t A;
  matrix_t B;
  double A_nums[25] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                       14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
  s21_create_matrix(5, 5, &A);
  set(A_nums, &A);
  int res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(complements_1) {
  int result = s21_calc_complements(NULL, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(complements_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(complements_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(10, 9, &A);
  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(complements_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &C);
  A.matrix[0][0] = 984.1238;
  C.matrix[0][0] = 984.1238;
  int res = s21_calc_complements(&A, &B);
  // output(&B);
  // printf("\n%lf\n", B.matrix[0][0]);
  // output(&C);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(complements_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_nums[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double result_nums[9] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  set(A_nums, &A);
  set(result_nums, &C);
  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST


START_TEST(test_transpose_1) {
  static double array[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  static double res_array[2][3] = {{1, 3, 5}, {2, 4, 6}};
  int row = 3;
  int col = 2;
  matrix_t A;
  matrix_t result;
  matrix_t correct_result;
  s21_create_matrix(row, col, &A);
  s21_create_matrix(col, row, &correct_result);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }

  for (int i = 0; i < col; i++)
    for (int j = 0; j < row; j++) {
      correct_result.matrix[i][j] = res_array[i][j];
    }

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);
  code = s21_eq_matrix(&result, &correct_result);
  ck_assert_int_eq(code, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&correct_result);
}
END_TEST

START_TEST(test_transpose_2) {
  matrix_t A;
  matrix_t *result = NULL;

  int code = s21_transpose(&A, result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_transpose_3) {
  matrix_t A;
  matrix_t result;

  A.matrix = NULL;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

void case_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  srunner_set_fork_status(runner, CK_NOFORK);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

Suite *s21_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_matrix");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_transpose_1);
  tcase_add_test(tc_core, test_transpose_2);
  tcase_add_test(tc_core, test_transpose_3);

  tcase_add_test(tc_core, test_calc_complements_2);
  tcase_add_test(tc_core, test_calc_complements_1);
  tcase_add_test(tc_core, test_calc_complements_3);
  tcase_add_test(tc_core, test_calc_complements_4);
  tcase_add_test(tc_core, test_inverse_matrix_1);
  tcase_add_test(tc_core, test_inverse_matrix_1);
  tcase_add_test(tc_core, test_inverse_matrix_2);
  tcase_add_test(tc_core, test_inverse_matrix_3);
  tcase_add_test(tc_core, test_inverse_matrix_4);
  tcase_add_test(tc_core, test_s21_sub_matrix);
  tcase_add_test(tc_core, test_s21_sum_matrix);
  tcase_add_test(tc_core, test_s21_eq_matrix);
  tcase_add_test(tc_core, test_s21_create_matrix);
  tcase_add_test(tc_core, multi_num_1);
  tcase_add_test(tc_core, multi_num_2);
  tcase_add_test(tc_core, multi_num_3);
  tcase_add_test(tc_core, multi_num_4);
  tcase_add_test(tc_core, multi_mat_1);
  tcase_add_test(tc_core, multi_mat_3);
  tcase_add_test(tc_core, multi_mat_4);
  tcase_add_test(tc_core, multi_mat_5);
  tcase_add_test(tc_core, multi_mat_6);
  tcase_add_test(tc_core, transpose_2);
  tcase_add_test(tc_core, transpose_1);
  tcase_add_test(tc_core, transpose_3);
  tcase_add_test(tc_core, transpose_4);
  tcase_add_test(tc_core, transpose_5);
  tcase_add_test(tc_core, transpose_6);
  tcase_add_test(tc_core, determinant_01);
  tcase_add_test(tc_core, determinant_02);
  tcase_add_test(tc_core, determinant_03);
  tcase_add_test(tc_core, determinant_05);
  tcase_add_test(tc_core, determinant_1);
  tcase_add_test(tc_core, determinant_2);
  tcase_add_test(tc_core, determinant_3);
  tcase_add_test(tc_core, determinant_4);
  tcase_add_test(tc_core, determinant_5);
  tcase_add_test(tc_core, determinant_6);
  tcase_add_test(tc_core, determinant_7);
  tcase_add_test(tc_core, complements_1);
  tcase_add_test(tc_core, complements_2);
  tcase_add_test(tc_core, complements_3);
  tcase_add_test(tc_core, complements_4);
  tcase_add_test(tc_core, complements_5);
  tcase_add_test(tc_core, inverse_1);
  tcase_add_test(tc_core, inverse_2);
  tcase_add_test(tc_core, inverse_3);
  tcase_add_test(tc_core, inverse_4);
  tcase_add_test(tc_core, inverse_5);
  tcase_add_test(tc_core, inverse_6);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int no_falied = 0;

  case_test(s21_matrix_suite(), &no_falied);
  return !no_falied ? 0 : 1;
}
