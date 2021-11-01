#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>
#include <string.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void fillRandMatrix(double **matrix, size_t size)
{
    size_t i = 0;
    size_t j = 0;
#pragma omp parallel for shared(matrix) private(i, j)
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            matrix[i][j] = (double)(rand()) / RAND_MAX * size;
        }
    }
}

double dgemmBlas(double **matrixA,
                 double **matrixB,
                 double **matrixC,
                 size_t size,
                 size_t threadsCount)
{
    omp_set_num_threads(threadsCount);
    double timerStart = 0;
    double timerStop = 0;

    int i = 0;
    int j = 0;
    int k = 0;
    timerStart = wtime();
#pragma omp parallel for shared(matrixA, matrixB, matrixC) private(j, k)
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            for (k = 0; k < size; k++)
            {
                matrixC[i][j] = matrixC[i][j] + matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    timerStop = wtime();

    return timerStop - timerStart;
}

int main(int argc, char *argv[])
{
    size_t matrixSize = 0;
    size_t threadsCount = 1;

    for (size_t i = 0; i < (size_t)(argc); i++)
    {
        if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--matrix-size"))
        {
            matrixSize = atoll(argv[i + 1]);
        }
        if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "--threads"))
        {
            threadsCount = atoll(argv[i + 1]);
        }
    }

    double **matrixA = malloc(matrixSize * sizeof(double *));
    double **matrixB = malloc(matrixSize * sizeof(double *));
    double **matrixC = malloc(matrixSize * sizeof(double *));

    for (size_t i = 0; i < matrixSize; i++)
    {
        matrixA[i] = malloc(matrixSize * sizeof(double));
        matrixB[i] = malloc(matrixSize * sizeof(double));
        matrixC[i] = malloc(matrixSize * sizeof(double));
    }

    fillRandMatrix(matrixA, matrixSize);
    fillRandMatrix(matrixB, matrixSize);

    double elapsedTime = dgemmBlas(matrixA, matrixB, matrixC, matrixSize, threadsCount);

    printf("%zux%zu;%f;%zu\n", matrixSize, matrixSize, elapsedTime, threadsCount);

    for (size_t i = 0; i < matrixSize; i++)
    {
        free(matrixA[i]);
        free(matrixB[i]);
        free(matrixC[i]);
    }

    free(matrixA);
    free(matrixB);
    free(matrixC);

    return EXIT_SUCCESS;
}