#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>
#include <string.h>
#include <pthread.h>

size_t matrixSize = 0;
size_t threadsCount = 1;
size_t localSize = 0;

double **matrixA = NULL;
double **matrixB = NULL;
double **matrixC = NULL;

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
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            matrix[i][j] = (double)(rand()) / RAND_MAX * size;
        }
    }
}

void *dgemmBlas(void *rank)
{
    long myRank = (long)rank;
    size_t i, j, k;
    size_t myFirstRow = myRank * localSize;
    size_t myLastRow = (myRank + 1) * localSize - 1;
    for (i = myFirstRow; i < myLastRow; i++)
    {
        for (j = 0; j < matrixSize; j++)
        {
            matrixC[i][j] = 0;
            for (k = 0; k < matrixSize; k++)
            {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
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

    localSize = matrixSize / threadsCount;

    matrixA = malloc(matrixSize * sizeof(double *));
    matrixB = malloc(matrixSize * sizeof(double *));
    matrixC = malloc(matrixSize * sizeof(double *));

    for (size_t i = 0; i < matrixSize; i++)
    {
        matrixA[i] = malloc(matrixSize * sizeof(double));
        matrixB[i] = malloc(matrixSize * sizeof(double));
        matrixC[i] = malloc(matrixSize * sizeof(double));
    }

    fillRandMatrix(matrixA, matrixSize);
    fillRandMatrix(matrixB, matrixSize);

    pthread_t *threads = malloc(threadsCount * sizeof(pthread_t));

    for (size_t i = 0; i < threadsCount; ++i)
    {
        int *p = NULL;
        pthread_create(&threads[i], NULL, dgemmBlas, (void *)(p));
    }

    double start = 0;
    double stop = 0;

    start = wtime();
    for (size_t i = 0; i < threadsCount; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    stop = wtime();

    double elapsedTime = stop - start;

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