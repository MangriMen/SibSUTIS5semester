#include <iostream>
#include <vector>
#include <cstring>
#include <chrono>
#include <iomanip>

using namespace std;

void fillRandMatrix(vector<vector<double>> &matrix)
{
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            matrix[i][j] = (double)(rand()) / RAND_MAX * (matrix.size());
        }
    }
}

double dgemmBlas(const vector<vector<double>> &matrixA,
                 const vector<vector<double>> &matrixB,
                 vector<vector<double>> &matrixC)
{
    if (matrixA.size() != matrixB.size())
    {
        return 0;
    }

    size_t matrixSize = matrixA.size();

    matrixC.clear();
    matrixC.shrink_to_fit();
    matrixC.resize(matrixSize, vector<double>(matrixSize, 0));

    auto timerStart = chrono::high_resolution_clock::now();
    auto timerStop = chrono::high_resolution_clock::now();

    timerStart = chrono::high_resolution_clock::now();
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            for (int k = 0; k < matrixSize; k++)
            {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    timerStop = chrono::high_resolution_clock::now();

    return chrono::duration<long double>(timerStop - timerStart).count();
}

double dgemmOpt1(const vector<vector<double>> &matrixA,
                 const vector<vector<double>> &matrixB,
                 vector<vector<double>> &matrixC)
{
    if (matrixA.size() != matrixB.size())
    {
        return 0;
    }

    size_t matrixSize = matrixA.size();

    matrixC.clear();
    matrixC.shrink_to_fit();
    matrixC.resize(matrixSize, vector<double>(matrixSize, 0));

    auto timerStart = chrono::high_resolution_clock::now();
    auto timerStop = chrono::high_resolution_clock::now();

    timerStart = chrono::high_resolution_clock::now();
    for (int i = 0; i < matrixSize; i++)
    {
        for (int k = 0; k < matrixSize; k++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    timerStop = chrono::high_resolution_clock::now();

    return chrono::duration<long double>(timerStop - timerStart).count();
}

int main(int argc, char *argv[])
{
    size_t matrixSize = 0;

    for (size_t i = 0; i < static_cast<size_t>(argc); i++)
    {
        if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--matrix-size"))
        {
            matrixSize = atoll(argv[i + 1]);
        }
    }

    vector<vector<double>> matrixA(matrixSize, vector<double>(matrixSize, 0));
    vector<vector<double>> matrixB(matrixSize, vector<double>(matrixSize, 0));
    vector<vector<double>> matrixC(matrixSize, vector<double>(matrixSize, 0));

    fillRandMatrix(matrixA);
    fillRandMatrix(matrixB);

    double elapsedTime = 0;

    for (size_t i = 0; i < static_cast<size_t>(argc); i++)
    {
        if (!strcmp(argv[i], "opt0"))
        {
            elapsedTime = dgemmBlas(matrixA, matrixB, matrixC);
        }
        else if (!strcmp(argv[i], "opt1"))
        {
            elapsedTime = dgemmOpt1(matrixA, matrixB, matrixC);
        }
    }

    cout << fixed << setprecision(16) << matrixSize << "x" << matrixSize << ";" << elapsedTime << endl;

    return EXIT_SUCCESS;
}