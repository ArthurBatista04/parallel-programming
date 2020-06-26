
#include "./matrix.h"
void print_result_matrix(int **res, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            printf("%d ", res[i][j]);
        printf("\n");
    }
}

int **init_matrix(int rows)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

void multiply_lines(int **matA, int **matB, int **res, int start, int end, int size)
{
    int i, j, k;
    for (i = start; i < end; i++)
    {
        for (j = 0; j < size; j++)
        {
            res[i][j] = 0;
            for (k = 0; k < size; k++)
                res[i][j] += matA[i][k] * matB[k][j];
        }
    }
}

void multiply_columns(int **matA, int **matB, int **res, int start, int end, int size)
{
    int i, j, k;
    for (i = 0; i < size; i++)
    {
        for (j = start; j < end; j++)
        {
            res[i][j] = 0;
            for (k = 0; k < size; k++)
                res[i][j] += matA[i][k] * matB[k][j];
        }
    }
}