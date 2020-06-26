#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
void print_result_matrix(int **res, int size);
int **init_matrix(int rows);
void multiply_lines(int **matA, int **matB, int **res, int start, int end, int size);
void multiply_columns(int **matA, int **matB, int **res, int start, int end, int size);
#endif