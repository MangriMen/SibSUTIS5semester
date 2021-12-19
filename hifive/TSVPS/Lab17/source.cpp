#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <cmath> 

#define MAX_ELEM 16777216

using namespace std;

string counter(string input) {
	int i = 0;
	int closingIndex = -1;

	while (i < input.size()) {
		while (i < input.size() && input[i] != ')') { i++; }
		closingIndex = i;
		if (closingIndex == input.size()) {
			break;
		}

		while (i > 0 && input[i] != '(') { i--; }

		if (input[i - 1] == '(' && closingIndex != -1 && input[closingIndex + 1] == ')') {
			input[closingIndex] = '-';
			input[i] = '-';
			closingIndex = -1;
		} else {
			if (input[closingIndex + 1] == ')') {
				while (i > 0 && (input[i] != '(' || input[i - 1] != '(')) { i--; }
				while (i > 0 && (input[i] == '(' || input[i - 1] == '(')) { i--; }
				i++;
				int tempClosing = closingIndex;
				while (closingIndex < input.size() && (input[closingIndex] == ')' || input[closingIndex + 1] == ')')) { closingIndex++; }
				if (input[i] == '(' && closingIndex != -1 && input[closingIndex] == ')') {
					input[closingIndex] = '-';
					input[i] = '-';
				}
				closingIndex = tempClosing;
				i = closingIndex;
			} else {
				i = closingIndex + 1;
			}
			
			closingIndex = -1;
		}

		i++;
	}

	input.erase(remove(input.begin(), input.end(), '-'), input.end());

	return input;
}

string brackets(const vector<long long>& matrices, long long& operationsCount) {
	const long long n = matrices.size() - 1;
	vector<vector<long long>> f(n, vector<long long>(n, 0));

	for (long long t = 1; t < n; t++) {
		for (long long k = 0; k < n - t; k++) {
			long long min_ = -1;

			for (long long j = k; j < k + t; j++) {
				long long checkMin = f[k][j] + f[j + 1][k + t] + matrices[k] * matrices[j + 1] * matrices[k + t + 1];
				if (min_ < 0 || checkMin < min_) {
					min_ = checkMin;
				}
			}

			f[k][k + t] = min_;
		}
	}
	operationsCount = f[0][n - 1];

	const long long outN = 4 * n - 1;
	vector<vector<bool>> fMin(n, vector<bool>(n, false));
	vector<string> out(outN);
	fMin[0][n - 1] = true;

	for (long long i = 0; i < outN; i++) {
		if ((i - 1) % 4 == 0) {
			out[i] = "[" + to_string(matrices[(i - 1) / 4]) + " x " + to_string(matrices[(i - 1) / 4 + 1]) + "]";
		}
		else if ((i + 1) % 4 == 0) {
			out[i] = "*";
		}
		else {
			out[i] = "";
		}
	}

	for (long long t = n - 1; t >= 1; t--) {
		for (long long k = 0; k < n - t; k++) {
			if (!fMin[k][k + t]) { continue; }

			for (long long j = k; j < k + t; j++) {
				if (f[k][j] + f[j + 1][k + t] + matrices[k] * matrices[j + 1] * matrices[k + t + 1] == f[k][k + t]) {
					fMin[k][j] = true;
					fMin[j + 1][k + t] = true;

					out[(k * 4 + 1) - 1] += '(';
					//	out[(k * 4 + 1)-1] += "\"" + to_string(t) + "\" - (";
					out[(j * 4 + 1) + 1] = ")" + out[(j * 4 + 1) + 1];
					out[((j + 1) * 4 + 1) - 1] += '(';
					//	out[((j + 1)*4 + 1)-1] += "\"" + to_string(t) + "\" - (";
					out[((k + t) * 4 + 1) + 1] = ")" + out[((k + t) * 4 + 1) + 1];
				}
			}
		}
	}

	string res;
	for (long long i = 0; i < outN; i++) {
		res += " " + out[i];
	}

	return res;
}

int main() {
	ifstream fileIn("data5.txt");
	if (!fileIn.is_open()) {
		cerr << "Unable to open file" << "\n";
		return EXIT_FAILURE;
	}

	long long n = 0;
	fileIn >> n;

	if (n < 2) {
		cerr << "The number of matrices is incorrect: " << n << "\n";
		return EXIT_FAILURE;
	}

	vector<long long> matrices(n + 1);
	for (size_t i = 0; i < matrices.size(); i++) {
		fileIn >> matrices[i];
		if (matrices[i] <= 0) {
			cerr << "Size is incorrect: " << matrices[i] << "\n";
			fileIn.close();
			return EXIT_FAILURE;
		}
	}
	
	fileIn.close();

	cout << "Matrices: " << n << ": ";

	cout << "[" << matrices[0] << " x " << matrices[1] << "]";
	for (int i = 1; i < n; i++) {
		cout << " * [" << matrices[i] << " x " << matrices[i + 1] << "]";
	}
	cout << "\n\n";

	long long operationsCount = 0;
	string order = counter(brackets(matrices, operationsCount));

	cout << "Multiplication: " << order << "\n\n";
	cout << "Estimated operations: " << operationsCount << "\n\n";

	return EXIT_SUCCESS;
}