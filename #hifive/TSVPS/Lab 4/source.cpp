#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <tuple>
using namespace std;

#define myPI 3.1415926535

size_t counter = 0;

namespace utils {
	template <typename T>
	string getSpacedElement(T element) {
		return ((element >= 0 ? " " : "") + to_string(element));
	}

	tuple<size_t, size_t> getNumberDecompositionBy2(size_t number) {
		for (int i = sqrt(number); i <= number; ++i) {
			if (number % i == 0) {
				return { i, number / i };
			}
		}
	}
}

namespace arrayTweaks {
	template <typename T>
	void fillArrayInc(vector<T>& arr, size_t size) {
		arr.clear();
		for (size_t i = 0; i < size; i += 1) {
			arr.push_back(static_cast<int>(i));
		}
	}

	template <typename T>
	void fillArrayRand(vector<T>& arr, size_t size) {
		arr.clear();
		for (size_t i = 0; i < size; i += 1) {
			arr.push_back(rand() % (size * size) - size);
		}
	}

	template <typename T>
	void printArrayLog(const vector<T>& arr, string message = "") {
		if (message != "") {
			cout << message << endl;
		}

		for (size_t i = 0; i < arr.size(); i += 1) {
			cout << arr[i] << " ";
		}

		cout << endl << endl;
	}

	template <typename T>
	void printArrayLog(const vector<complex<T>>& arr, string message = "") {
		if (message != "") {
			cout << message << endl;
		}

		cout.precision(6);
		cout << fixed;
		for (size_t i = 0; i < arr.size(); i += 1) {
			cout << utils::getSpacedElement(arr[i].real()) << " "
				<< utils::getSpacedElement(arr[i].imag()) << endl;
		}

		cout << endl;
	}
}

vector<complex<double>> getDiscreteFourierTransform(const vector<double>& data) {
	if (data.size() == 0) return vector<complex<double>>();

	const double REVERSE_N = 1.0 / static_cast<double>(data.size());
	const double EXPR_PART = -2.0 * myPI * REVERSE_N;
	vector<complex<double>> resultArray(data.size());
	complex<double> expResult;

	for (size_t k = 0; k < data.size(); k += 1) {
		for (size_t j = 0; j < data.size(); j += 1) {
			expResult = exp(1i * EXPR_PART * static_cast<double>(k) * static_cast<double>(j));
			resultArray[k] += data[j] * expResult;
		}

		resultArray[k] *= REVERSE_N;
	}

	return resultArray;
}

vector<double> getReverseDiscreteFourierTransform(const vector<complex<double>>& data) {
	if (data.size() == 0) return vector<double>();

	const double EXPR_PART = 2.0 * myPI * 1.0 / static_cast<double>(data.size());
	vector<double> resultArray(data.size());
	complex<double> expResult;

	for (size_t k = 0; k < data.size(); k += 1) {
		for (size_t j = 0; j < data.size(); j += 1) {
			expResult = exp(1i * EXPR_PART * static_cast<double>(k) * static_cast<double>(j));
			resultArray[k] += (data[j] * expResult).real();
		}
	}

	return resultArray;
}

vector<complex<double>> getSemiFastFourierTransform(const vector<double>& data) {
	if (data.size() == 0) return vector<complex<double>>();

	size_t p1, p2;
	tie(p1, p2) = utils::getNumberDecompositionBy2(data.size());

	vector<vector<complex<double>>> temp1(p1, vector<complex<double>>(p1));
	vector<vector<complex<double>>> temp2(p1, vector<complex<double>>(p1));

	double REVERSE_P1 = 1.0 / static_cast<double>(p1);
	double REVERSE_P2 = 1.0 / static_cast<double>(p2);
	const double EXPR_PART = -2.0 * myPI * REVERSE_P1;

	for (size_t k1 = 0; k1 < p1; k1++) {
		for (size_t j2 = 0; j2 < p2; j2++) {
			for (size_t j1 = 0; j1 < p1; j1++) {
				temp1[k1][j2] += data[j2 + p2 * j1] * exp(1i * EXPR_PART * (static_cast<double>(j1) * static_cast<double>(k1)));
				counter++;
			}
			temp1[k1][j2] *= REVERSE_P1;
		}
	}

	for (size_t k1 = 0; k1 < p1; k1++) {
		for (size_t k2 = 0; k2 < p2; k2++) {
			for (size_t j2 = 0; j2 < p2; j2++) {
				temp2[k1][k2] += temp1[k1][j2] * exp(1i * EXPR_PART * (static_cast<double>(j2) * (static_cast<double>(k1) + static_cast<double>(p1) * static_cast<double>(k2)) / static_cast<double>(p2)));
				counter++;
			}
			temp2[k1][k2] *= REVERSE_P2;
		}
	}

	temp1.clear();
	temp1.~vector();

	vector<complex<double>> out(p1 * p2);
	for (size_t k1 = 0, j = 0; k1 < p2; k1++) {
		for (size_t k2 = 0; k2 < p1; k2++, j++) {
			out[j] = temp2[k2][k1];
		}
	}

	temp2.clear();
	temp2.~vector();

	return out;
}

vector<double> getReverseSemiFastFourierTransform(const vector<complex<double>>& data) {
	if (data.size() == 0) return vector<double>();

	size_t p1, p2;
	tie(p1, p2) = utils::getNumberDecompositionBy2(data.size());

	vector<vector<complex<double>>> temp1(p1, vector<complex<double>>(p1));
	vector<vector<complex<double>>> temp2(temp1);

	const double REVERSE_P1 = 1.0 / static_cast<double>(p1);
	const double EXPR_PART = 2.0 * myPI * REVERSE_P1;

	for (size_t k1 = 0; k1 < p1; k1++) {
		for (size_t j2 = 0; j2 < p2; j2++) {
			for (size_t j1 = 0; j1 < p1; j1++) {
				temp1[k1][j2] += data[j2 + p2 * j1] * exp(1i * EXPR_PART * (static_cast<double>(j1) * static_cast<double>(k1)));
			}
		}
	}

	for (size_t k1 = 0; k1 < p1; k1++) {
		for (size_t k2 = 0; k2 < p2; k2++) {
			for (size_t j2 = 0; j2 < p2; j2++) {
				temp2[k1][k2] += temp1[k1][j2] * exp(1i * EXPR_PART * (static_cast<double>(j2) * (static_cast<double>(k1) + static_cast<double>(p1) * static_cast<double>(k2)) / static_cast<double>(p2)));
			}
		}
	}

	temp1.clear();
	temp1.~vector();

	vector<double> out(p1 * p2);
	for (size_t k1 = 0, j = 0; k1 < p2; k1++) {
		for (size_t k2 = 0; k2 < p1; k2++, j++) {
			out[j] = temp2[k2][k1].real();
		}
	}

	temp2.clear();
	temp2.~vector();

	return out;
}

int main() {
	srand(time(NULL));

	const int VECTOR_SIZE = 16;
	vector<size_t> sizes {5*5, 10*10, 20*20};

	for (int j = 0; j < sizes.size(); ++j) {
		counter = 0;
		vector<double> startArray(sizes[j], 0);
	
		for (int i = 0; i < sizes[j]; i += 1) {
			startArray[i] = i*i;
		}

		vector<complex<double>> semiFastFourier = getSemiFastFourierTransform(startArray);
		//vector<double> reverseSemiFastFourier = getReverseSemiFastFourierTransform(semiFastFourier);

		cout << "Size: " << sizes[j] << endl;
		cout << "Counter: " << counter << endl << endl;
	}
	//vector<complex<double>> discreteFourier = getDiscreteFourierTransform(startArray);
	//vector<double> reverseDiscreteFourier = getReverseDiscreteFourierTransform(discreteFourier);
	//vector<complex<double>> semiFastFourier = getSemiFastFourierTransform(startArray);
	//vector<double> reverseSemiFastFourier = getReverseSemiFastFourierTransform(semiFastFourier);

	//arrayTweaks::printArrayLog(startArray, "Original array:");
	//arrayTweaks::printArrayLog(discreteFourier, "Array aquired by DF:");
	//arrayTweaks::printArrayLog(reverseDiscreteFourier, "Array aquired by RDF:");
	//arrayTweaks::printArrayLog(semiFastFourier, "Array aquired by SFF:");
	//arrayTweaks::printArrayLog(reverseSemiFastFourier, "Array aquired by RSFF:");

	return 0;
}
