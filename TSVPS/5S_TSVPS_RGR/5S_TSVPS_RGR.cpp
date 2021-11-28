#include <iostream>
#include <chrono>
#include "../5S_TSVPS_Lab11/utils.hpp"

using namespace std;

double dgemmBlas(const vector<vector<string>>& matrixA,
	const vector<vector<string>>& matrixB,
	vector<vector<string>>& matrixC,
	string(*function)(const string&, const string&))
{
	if (matrixA.size() != matrixB.size())
	{
		return 0;
	}

	size_t matrixSize = matrixA.size();

	matrixC.clear();
	matrixC.shrink_to_fit();
	matrixC.resize(matrixSize, vector<string>(matrixSize, "0"));

	auto timerStart = chrono::high_resolution_clock::now();
	auto timerStop = chrono::high_resolution_clock::now();

	timerStart = chrono::high_resolution_clock::now();
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			for (int k = 0; k < matrixSize; k++)
			{
				matrixC[i][j] = add(matrixC[i][j], function(matrixA[i][k], matrixB[k][j]));
			}
		}
	}
	timerStop = chrono::high_resolution_clock::now();

	return chrono::duration<long double>(timerStop - timerStart).count();
}

constexpr size_t MATRIX_SIZE = 100;

int main()
{
	vector<vector<string>> A(MATRIX_SIZE, vector<string>(MATRIX_SIZE, "0"));
	vector<vector<string>> B(MATRIX_SIZE, vector<string>(MATRIX_SIZE, "0"));
	vector<vector<string>> C(MATRIX_SIZE, vector<string>(MATRIX_SIZE, "0"));

	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			A[i][j] = to_string(static_cast<long long>(pow((1), (i + j))));
			B[i][j] = to_string(i + j);
			//cout << "A[" << i << "]" << "[" << j << "]: " << A[i][j] << endl;
			//cout << "B[" << i << "]" << "[" << j << "]: " << B[i][j] << endl;
		}
	}

	cout << "Regular multiply time: " << dgemmBlas(A, B, C, regularMultiply) << endl;
	cout << "Fast multiply time: " << dgemmBlas(A, B, C, fastMultiply) << endl;

	cout << endl;

	cout << "Regular multiply" << endl;
	cout << "\tSum, Sub  op: " << regSumSub << endl;
	cout << "\tMult, Div op: " << regMultDiv << endl;

	cout << "Fast multiply" << endl;
	cout << "\tSum, Sub  op: " << fastSumSub << endl;
	cout << "\tMult, Div op: " << fastMultDiv << endl;
}
