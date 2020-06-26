#include "./main.h"
#include "./matrix.h"

void *mm(void *thread_in)
{
    thread_info *info = (thread_info *)thread_in;
    int low = (info->size * info->thread_id) / info->num_threads;
    int high = (info->size * (info->thread_id + 1)) / info->num_threads;
    if (info->mm_mode == 0)
    {
        multiply_lines(info->matA, info->matB, info->res, low, high, info->size);
    }
    else if (info->mm_mode == 1)
    {
        multiply_columns(info->matA, info->matB, info->res, low, high, info->size);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

params *init_params(char **args, int size)
{
    params *input = malloc(sizeof(params));
    input->print = FALSE;
    input->matrix_size = 0;
    input->num_threads = 0;
    input->mm_mode = -1;
    int opt;
    while ((opt = getopt(size, args, "t:m:d:hv")) != -1)
    {
        switch (opt)
        {
        case THREAD_FLAG:
            input->num_threads = strtoul(optarg, NULL, 0);
            break;
        case MATRIX_DIMENSION_FLAG:
            input->matrix_size = strtoul(optarg, NULL, 0);
            break;
        case PRINT_FLAG:
            input->print = TRUE;
            break;
        case MM_MODE_FLAG:
            input->mm_mode = strtoul(optarg, NULL, 0);
            break;
        case HELP_FLAG:
            check_help(args[0]);
            break;
        case '?':
            exit(EXIT_FAILURE);
        default:
            abort();
        }
    }
    if (is_valid_input(input))
        return input;
    fprintf(stderr, "%s invalid input!", args[0]);
    exit(EXIT_FAILURE);
}

int is_valid_input(params *input)
{
    return (input->matrix_size > 0 && (input->mm_mode == 0 || input->mm_mode == 1) && input->num_threads > 0);
}

void check_erro(int code)
{
    if (code)
    {
        printf("ERROR; return code from pthread_create() is %d\n", code);
        exit(-1);
    }
}

void check_help(char *arg)
{
    fprintf(stderr, "Usage: %s [-t] [-m] [-d] optional[-v -h]\n",
            arg);
    fprintf(stderr, "-d (matrix distribution):\n0-lines\n1-columns\n");
    fprintf(stderr, "-t (number of threads)\n");
    fprintf(stderr, "-m (matrix dimension)\n");
    fprintf(stderr, "-v (print matrix information)");
    fprintf(stderr, "-h (help)");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{

    time_t time_start = time(NULL);
    srand((unsigned)time(&time_start));
    params *input = init_params(argv, argc);
    pthread_t threads[input->num_threads];
    int **matA = init_matrix(input->matrix_size);
    int **matB = init_matrix(input->matrix_size);
    int **res = init_matrix(input->matrix_size);
    int rc;
    long t;
    for (t = 0; t < input->num_threads; t++)
    {
        printf("In main: creating thread %ld\n", t + 1);
        thread_info *info = malloc(sizeof(thread_info));
        info->matA = matA;
        info->matB = matB;
        info->res = res;
        info->size = input->matrix_size;
        info->num_threads = input->num_threads;
        info->mm_mode = input->mm_mode;
        info->thread_id = t;
        rc = pthread_create(&threads[t], NULL, mm, info);
        check_erro(rc);
    }
    for (t = 0; t < input->num_threads; t++)
    {
        rc = pthread_join(threads[t], NULL);
        check_erro(rc);
        printf("In main: thread %ld has finished processing\n", t + 1);
    }

    if (input->print)
    {

        printf("Matrix A\n");
        print_result_matrix(matA, input->matrix_size);
        printf("Matrix B\n");
        print_result_matrix(matB, input->matrix_size);
        printf("End result matrix is \n");
        print_result_matrix(res, input->matrix_size);
    }
    time_t time_end = time(NULL);
    printf("Time elpased is %d seconds", (time_end - time_start));
    return 0;
}
