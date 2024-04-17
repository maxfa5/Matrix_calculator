#ifndef TESTS_H
#define TESTS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#define SUCCESS 1
#define FAILURE 0
#define ACCURACY 1e-7

enum result_code { OK, INCORRECT_MATRIX, CALCULATION_ERROR };

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void set(double *nums, matrix_t *A);
int is_valid(matrix_t *A);
void swap(int str1, int str2, matrix_t *A);
int check_null_under(matrix_t *A, int column, int row);
void to_triangle_form(matrix_t *A);
void rows_to_null(matrix_t *A, int start_row, int column);
double mul_diagonal(matrix_t *A);
int swap_zeros(matrix_t *A, int sign, int column);
int not_null_str(matrix_t *A);
double minor(matrix_t *A, int row, int column);
int is_valid_x_y(matrix_t *A);
void s21_copy_matrix(matrix_t *A, matrix_t *B);
#endif