#ifndef MAIN_H
#define MAIN_H
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#define THREAD_FLAG 't'
#define MATRIX_DIMENSION_FLAG 'm'
#define MM_MODE_FLAG 'd'
#define PRINT_FLAG 'v'
#define HELP_FLAG 'h'
#define TRUE 1;
#define FALSE 0;

typedef struct params
{
    int num_threads;
    int matrix_size;
    int mm_mode;
    int print;
} params;

typedef struct thread_info
{
    int **matA;
    int **matB;
    int **res;
    int size;
    int thread_id;
    int num_threads;
    int mm_mode;
} thread_info;

void *mm(void *thread_in);
int check_input(params *input);
void check_help(char *arg);
params *init_params(char **args, int size);
void check_erro(int code);
#endif