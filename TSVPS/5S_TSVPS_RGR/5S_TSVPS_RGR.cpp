#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;

size_t regularSumCounter = 0;
size_t regularMulCounter = 0;
size_t fastSumCounter = 0;
size_t fastMulCounter = 0;

template<typename T = int>
void dgemmBlas(const vector<vector<T>>& matrixA,
	const vector<vector<T>>& matrixB,
	vector<vector<T>>& matrixC)
{
	if (matrixA.size() != matrixB.size())
	{
		return;
	}

	size_t matrixSize = matrixA.size();

	matrixC.clear();
	matrixC.shrink_to_fit();
	matrixC.resize(matrixSize, vector<T>(matrixSize));

	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			for (int k = 0; k < matrixSize; k++)
			{
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
				regularSumCounter++;
				regularMulCounter++;
			}
		}
	}
}

#define MAT1(matrix) matrix[0][0]
#define MAT2(matrix) matrix[0][1]
#define MAT3(matrix) matrix[1][0]
#define MAT4(matrix) matrix[1][1]

template<typename T>
void copyQuarterOfMatrix(vector<vector<T*>>& matrix,
	vector<vector<T*>>& M, size_t quarterNum) {
	size_t partI = 0;
	size_t partJ = 0;

	partI = (quarterNum == 2 || quarterNum == 4) ? matrix.size() / 2 : 0;
	partJ = (quarterNum == 3 || quarterNum == 4) ? matrix.size() / 2 : 0;

	for (size_t startI = partI, i = 0; i < matrix.size() / 2; startI++, i++) {
		for (size_t startJ = partJ, j = 0; j < matrix.size() / 2; startJ++, j++)
		{
			M[i][j] = matrix[startI][startJ];
		}
	}
}

template<typename T>
void copyAllQuarterOfMatrix(vector<vector<T*>>& matrix,
	vector<vector<T*>>& M1,
	vector<vector<T*>>& M2,
	vector<vector<T*>>& M3,
	vector<vector<T*>>& M4)
{
	copyQuarterOfMatrix(matrix, M1, 1);
	copyQuarterOfMatrix(matrix, M2, 2);
	copyQuarterOfMatrix(matrix, M3, 3);
	copyQuarterOfMatrix(matrix, M4, 4);
}


template<typename T>
void fastMatrixMultiplyAction(vector<vector<T*>>& A,
	vector<vector<T*>>& B,
	vector<vector<T*>>& C) {

	size_t sumCounter = 18;
	fastMulCounter += 7 * (A.size() - 1);

	if (A.size() > 2) {
		size_t matrixSize = A.size();
		size_t matrixHalfSize = A.size() / 2;

		vector<vector<T*>> A1(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));
		vector<vector<T*>> A2(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));
		vector<vector<T*>> A3(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));
		vector<vector<T*>> A4(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));

		vector<vector<T*>> B1(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));
		vector<vector<T*>> B2(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));
		vector<vector<T*>> B3(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));
		vector<vector<T*>> B4(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));

		vector<vector<T*>> C1(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));
		vector<vector<T*>> C2(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));
		vector<vector<T*>> C3(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));
		vector<vector<T*>> C4(matrixHalfSize, vector<T*>(matrixHalfSize, nullptr));

		copyAllQuarterOfMatrix(A, A1, A2, A3, A4);
		copyAllQuarterOfMatrix(B, B1, B2, B3, B4);
		copyAllQuarterOfMatrix(C, C1, C2, C3, C4);

		fastMatrixMultiplyAction(A1, B1, C1);
		fastMatrixMultiplyAction(A2, B2, C2);
		fastMatrixMultiplyAction(A3, B3, C3);
		fastMatrixMultiplyAction(A4, B4, C4);

		fastSumCounter += sumCounter * 18 * 4;
	}
	else if (A.size() == 2) {
		auto M1 = (*MAT2(A) - *MAT4(A)) * (*MAT3(B) + *MAT4(B));
		auto M2 = (*MAT1(A) + *MAT4(A)) * (*MAT1(B) + *MAT4(B));
		auto M3 = (*MAT1(A) - *MAT3(A)) * (*MAT1(B) + *MAT2(B));
		auto M4 = (*MAT1(A) + *MAT2(A)) * *MAT4(B);
		auto M5 = *MAT1(A) * (*MAT2(B) - *MAT4(B));
		auto M6 = *MAT4(A) * (*MAT3(B) - *MAT1(B));
		auto M7 = (*MAT3(A) + *MAT4(A)) * *MAT1(B);

		*MAT1(C) = M1 + M2 - M4 + M6;
		*MAT2(C) = M4 + M5;
		*MAT3(C) = M6 + M7;
		*MAT4(C) = M2 - M3 + M5 - M7;
		fastSumCounter += sumCounter;
	}

}

template<typename T>
void fastMatrixMultiply(vector<vector<T>>& matrixA,
	vector<vector<T>>& matrixB,
	vector<vector<T>>& matrixC) {

	if (matrixA.size() != matrixB.size())
	{
		return;
	}

	size_t matrixSize = matrixA.size();

	matrixC.clear();
	matrixC.shrink_to_fit();
	matrixC.resize(matrixSize, vector<T>(matrixSize));

	vector<vector<T*>> pA(matrixSize, vector<T*>(matrixSize, nullptr));
	vector<vector<T*>> pB(matrixSize, vector<T*>(matrixSize, nullptr));
	vector<vector<T*>> pC(matrixSize, vector<T*>(matrixSize, nullptr));

	for (size_t i = 0; i < matrixSize; i++)
	{
		for (size_t j = 0; j < matrixSize; j++)
		{
			pA[i][j] = &matrixA[i][j];
			pB[i][j] = &matrixB[i][j];
			pC[i][j] = &matrixC[i][j];
		}
	}

	fastMatrixMultiplyAction(pA, pB, pC);
}

int main()
{
	ofstream out;
	out.open("out.csv", ios::out);
	if (!out.is_open())
	{
		cerr << "Unable to create output file." << endl;
		return EXIT_FAILURE;
	}
	std::cout.rdbuf(out.rdbuf());

	cout << "Size;Regular sum;Regular mul;Fast sum;Fast mul;Regular total;Fast total" << "\n";

	for (size_t matrixSize = 2; matrixSize <= 512; matrixSize *= 2) {
		regularSumCounter = 0;
		regularMulCounter = 0;
		fastSumCounter = 0;
		fastMulCounter = 0;

		vector<vector<long long>> A(matrixSize, vector<long long>(matrixSize));
		vector<vector<long long>> B(matrixSize, vector<long long>(matrixSize));
		vector<vector<long long>> C(matrixSize, vector<long long>(matrixSize));

		for (size_t i = 0; i < matrixSize; i++)
		{
			for (size_t j = 0; j < matrixSize; j++)
			{
				A[i][j] = static_cast<size_t>(pow(-1, i + j));
				B[i][j] = i + j;
			}
		}

		dgemmBlas(A, B, C);
		fastMatrixMultiply(A, B, C);

		cout
			<< matrixSize << ";"
			<< regularSumCounter << ";"
			<< regularMulCounter << ";"
			<< fastSumCounter << ";"
			<< fastMulCounter << ";"
			<< regularSumCounter + regularMulCounter << ";"
			<< fastSumCounter + fastMulCounter << endl;
	}

	return EXIT_SUCCESS;
}
