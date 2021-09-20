#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cmath>
#define clock_ chrono::high_resolution_clock
#define MHz 3600.0

using namespace std;

struct Comma final : std::numpunct<char>
{
    char do_decimal_point() const override { return ','; }
};

template <typename T>
vector<T> matrix_vector_multiply(const vector<vector<T>> &matrix, const vector<T> &vec)
{
    vector<T> out(vec.size(), 0);
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            out[i] = matrix[i][j] * vec[j];
        }
    }
    return out;
}

double test_int(size_t n, size_t m)
{
    vector<vector<int>> matrix(n, vector<int>(m, 0));
    vector<int> vec(m, 0);
    vector<int> out;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            matrix[i][j] = rand() % (n * m);
        }
    }

    for (size_t i = 0; i < m; i++)
    {
        vec[i] = rand() % (n * n);
    }

    clock_::time_point start = clock_::now();

    out = matrix_vector_multiply(matrix, vec);

    clock_::time_point end = clock_::now();

    return chrono::duration<double>(end - start).count();
}

double test_double(size_t n, size_t m)
{
    vector<vector<double>> matrix(n, vector<double>(m, 0));
    vector<double> vec(m, 0);
    vector<double> out;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            matrix[i][j] = (double)(rand()) / RAND_MAX * (n * m);
        }
    }

    for (size_t i = 0; i < m; i++)
    {
        vec[i] = (double)(rand()) / RAND_MAX * (n * n);
    }

    clock_::time_point start = clock_::now();

    out = matrix_vector_multiply(matrix, vec);

    clock_::time_point end = clock_::now();

    return chrono::duration<double>(end - start).count();
}

double test_float(size_t n, size_t m)
{
    vector<vector<double>> matrix(n, vector<double>(m, 0));
    vector<double> vec(m, 0);
    vector<double> out;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            matrix[i][j] = (double)(rand()) / RAND_MAX * (n * m);
        }
    }

    for (size_t i = 0; i < m; i++)
    {
        vec[i] = (double)(rand()) / RAND_MAX * (n * n);
    }

    clock_::time_point start = clock_::now();

    out = matrix_vector_multiply(matrix, vec);

    clock_::time_point end = clock_::now();

    return chrono::duration<double>(end - start).count();
}

void printHeader(size_t testCount)
{
    cout.precision(8);
    cout.imbue(std::locale(std::locale::classic(), new Comma));
    cout << fixed;

    cout << "Task;";
    cout << "OpType;";
    cout << "Opt;";
    cout << "InsCount;";
    cout << "Timer;";
    for (size_t i = 0; i < testCount; i++)
    {
        cout << i << ";";
    }
    cout << "AvTime;";
    cout << "AbsError;";
    cout << "RelError;";
    cout << "TaskPerf;" << endl;
}

template <typename T>
void printTask(string taskName, string opType, string opt, size_t testCount, vector<T> points, double avg, double absError, double relError)
{
    cout << taskName << ";";
    cout << opType << ";";
    cout << opt << ";";
    cout << testCount << ";";
    cout << "chrono;";
    for (size_t i = 0; i < testCount; i++)
    {
        cout << points[i] << ";";
    }
    cout << avg << ";";
    cout << absError << ";";
    cout << relError << "%" << ";";
    cout << 100.0 - relError  << ";" << endl;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    size_t testCount = 10;
    if (argc == 2 && atoi(argv[1]) > 10)
    {
        testCount = atoi(argv[1]);
    }

    size_t n = 1000;
    size_t m = n;

    vector<double> intPoints(testCount, 0);
    vector<double> floatPoints(testCount, 0);
    vector<double> doublePoints(testCount, 0);
    for (size_t i = 0; i < testCount; i++)
    {
        intPoints[i] = test_int(n, m);
        floatPoints[i] = test_float(n, m);
        doublePoints[i] = test_double(n, m);
    }

    double avgInt = 0;
    double avgFloat = 0;
    double avgDouble = 0;
    double matInt = 0;
    double matIntSquare = 0;
    double matFloat = 0;
    double matFloatSquare = 0;
    double matDouble = 0;
    double matDoubleSquare = 0;
    for (size_t i = 0; i < testCount; i++)
    {
        avgInt += intPoints[i];
        matInt += i * intPoints[i];
        matIntSquare += (i * i) * intPoints[i];
        avgFloat += floatPoints[i];
        matFloat += i * floatPoints[i];
        matFloatSquare += (i * i) * floatPoints[i];
        avgDouble += doublePoints[i];
        matDouble += i * doublePoints[i];
        matDoubleSquare += (i * i) * doublePoints[i];
    }
    double allInt = avgInt;
    double allFloat = avgFloat;
    double allDouble = avgDouble;
    avgInt /= testCount;
    avgFloat /= testCount;
    avgDouble /= testCount;

    // double dispInt = matIntSquare - (matInt * matInt);
    // double dispDouble = matDoubleSquare - (matDouble * matDouble);

    // double sDevInt = sqrt(dispInt);
    // double sDevDouble = sqrt(dispDouble);

    double absErrorInt = abs(testCount / (MHz * 1000 * 100000) - allInt / testCount);
    double absErrorFloat = abs(testCount / (MHz * 1000 * 100000) - allFloat / testCount);
    double absErrorDouble = abs(testCount / (MHz * 1000 * 100000) - allDouble / testCount);

    double relErrorInt = 0;
    double relErrorFloat = 0;
    double relErrorDouble = 0;

    relErrorInt = absErrorInt / (allInt / testCount);
    relErrorFloat = absErrorFloat / (allFloat / testCount);
    relErrorDouble = absErrorDouble / (allDouble / testCount);
    string opt = "O1";

    printHeader(testCount);
    printTask("dgemv", "int", opt, testCount, intPoints, avgInt, absErrorInt, relErrorInt);
    printTask("dgemv", "float", opt, testCount, floatPoints, avgFloat, absErrorFloat, relErrorFloat);
    printTask("dgemv", "double", opt, testCount, doublePoints, avgDouble, absErrorDouble, relErrorDouble);

    return EXIT_SUCCESS;
}