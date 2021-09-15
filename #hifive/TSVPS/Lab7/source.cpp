#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <tuple>
using namespace std;


namespace utils {
	size_t resizeDoubleTheMax(vector<double>& a, vector<double>& b) {
		size_t newSize = 0;

		if (a.size() < b.size()) {
			newSize = b.size();
			a.resize(newSize, 0.0);
		}
		else {
			newSize = a.size();
			b.resize(newSize, 0.0);
		}

		newSize *= 2;
		a.resize(newSize, 0);
		b.resize(newSize, 0);

		return newSize;
	}

	tuple<size_t, size_t> getNumberDecompositionBy2(size_t number) {
		for (int i = sqrt(number); i <= number; ++i) {
			if (number % i == 0) {
				return { i, number / i };
			}
		}
	}

	enum {
		DISCRETE,
		SEMI_FAST,
	};
}

size_t counter = 0;
size_t counterDF = 0;
size_t counterSF = 0;

vector<complex<double>> getDiscreteFourierTransform(const vector<double>& data) {
	if (data.size() == 0) return vector<complex<double>>();

	vector<complex<double>> out(data.size());
	complex<double> exp_result;
	const double reverseN = 1.0 / static_cast<double>(data.size());
	const double EXPR_PART = -2.0 * M_PI * reverseN;

	for (size_t k = 0; k < data.size(); k++) {
		for (size_t j = 0; j < data.size(); j++) {
			exp_result = exp(1i * EXPR_PART * static_cast<double>(k) * static_cast<double>(j));
			out[k] += data[j] * exp_result;
			counterDF++;
		}
		out[k] *= reverseN;
	}

	return out;
}

vector<double> getReverseDiscreteFourierTransform(const vector<complex<double>>& data) {
	if (data.size() == 0) return vector<double>();

	vector<double> out(data.size());
	complex<double> exp_result;
	const double reverseN = 1.0 / static_cast<double>(data.size());
	const double EXPR_PART = 2.0 * M_PI * reverseN;

	for (size_t k = 0; k < data.size(); k++) {
		for (size_t j = 0; j < data.size(); j++) {
			exp_result = exp(1i * EXPR_PART * static_cast<double>(k) * static_cast<double>(j));
			out[k] += (data[j] * exp_result).real();
			counterDF++;
		}
	}

	return out;
}

vector<complex<double>> getSemiFastFourierTransform(const vector<double>& data) {
	if (data.size() == 0) return vector<complex<double>>();

	size_t p1, p2;
	tie(p1, p2) = utils::getNumberDecompositionBy2(data.size());

	vector<vector<complex<double>>> temp1(p1, vector<complex<double>>(p1));
	vector<vector<complex<double>>> temp2(p1, vector<complex<double>>(p1));

	double REVERSE_P1 = 1.0 / static_cast<double>(p1);
	double REVERSE_P2 = 1.0 / static_cast<double>(p2);
	const double EXPR_PART = -2.0 * M_PI * REVERSE_P1;

	for (size_t k1 = 0; k1 < p1; k1++) {
		for (size_t j2 = 0; j2 < p2; j2++) {
			for (size_t j1 = 0; j1 < p1; j1++) {
				temp1[k1][j2] += data[j2 + p2 * j1] * exp(1i * EXPR_PART * (static_cast<double>(j1) * static_cast<double>(k1)));
				counterSF++;
			}
			temp1[k1][j2] *= REVERSE_P1;
		}
	}

	for (size_t k1 = 0; k1 < p1; k1++) {
		for (size_t k2 = 0; k2 < p2; k2++) {
			for (size_t j2 = 0; j2 < p2; j2++) {
				temp2[k1][k2] += temp1[k1][j2] * exp(1i * EXPR_PART * (static_cast<double>(j2) * (static_cast<double>(k1) + static_cast<double>(p1) * static_cast<double>(k2)) / static_cast<double>(p2)));
				counterSF++;
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
	const double EXPR_PART = 2.0 * M_PI * REVERSE_P1;

	for (size_t k1 = 0; k1 < p1; k1++) {
		for (size_t j2 = 0; j2 < p2; j2++) {
			for (size_t j1 = 0; j1 < p1; j1++) {
				temp1[k1][j2] += data[j2 + p2 * j1] * exp(1i * EXPR_PART * (static_cast<double>(j1) * static_cast<double>(k1)));
				counterSF++;
			}
		}
	}

	for (size_t k1 = 0; k1 < p1; k1++) {
		for (size_t k2 = 0; k2 < p2; k2++) {
			for (size_t j2 = 0; j2 < p2; j2++) {
				temp2[k1][k2] += temp1[k1][j2] * exp(1i * EXPR_PART * (static_cast<double>(j2) * (static_cast<double>(k1) + static_cast<double>(p1) * static_cast<double>(k2)) / static_cast<double>(p2)));
				counterSF++;
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

vector<double> convolute(const vector<double>& x, const vector<double>& h) {
	if ((x.size() == 0) && (h.size() == 0)) return vector<double>();

	vector<double> a;
	vector<double> b;

	if (x.size() < h.size()) {
		a = x;
		b = h;
	}
	else {
		a = h;
		b = x;
	}

	vector<double> result(a.size() + b.size() - 1, 0);

	for (size_t k = 0; k < a.size(); k++) {
		for (size_t l = 0; l < b.size(); l++) {
			result[l + k] += a[k] * b[l];
			counter++;
		}
	}

	return result;
}

vector<double> forierConvolute(vector<double> a, vector<double> b, int type) {
	size_t newSize = utils::resizeDoubleTheMax(a, b);
	vector<double> out(newSize, 0);
	vector<complex<double>> temp(newSize, 0);

	vector<complex<double>> fourierA = getDiscreteFourierTransform(a);
	vector<complex<double>> fourierB = getDiscreteFourierTransform(b);

	for (size_t i = 0; i < newSize; i++) {
		temp[i] = static_cast<double>(newSize) * fourierA[i] * fourierB[i];
		counterDF++;
	}

	if (type == utils::DISCRETE) {
		out = getReverseDiscreteFourierTransform(temp);
	}
	else if (type == utils::SEMI_FAST) {
		out = getReverseSemiFastFourierTransform(temp);
	}

	return out;
}

int main() {
	vector<int> sizes = { 16, 64, 128, 512 };
	cout << "Convolutions:" << endl
		<< endl << "===================" << endl;
	for (size_t i = 0; i < sizes.size(); ++i) {
		cout << "On " << sizes[i] << " elements:" << endl << endl;

		vector<double> dataA(sizes[i], 0);
		vector<double> dataB(sizes[i], 0);

		for (size_t j = 0; j < dataA.size(); j++) {
			dataA[j] = j;
		}

		for (size_t j = 0; j < dataB.size(); j++) {
			dataB[j] = j;
		}

		counter = 0;
		counterDF = 0;
		counterSF = 0;

		vector<double> out = convolute(dataA, dataB);
		vector<double> outDF = forierConvolute(dataA, dataB, utils::DISCRETE);
		vector<double> outSF = forierConvolute(dataA, dataB, utils::SEMI_FAST);

		cout << "Regular: " << counter << endl;
		cout << "DFT: " << counterDF << endl;
		cout << "SFFT: " << counterSF << endl;
		cout << "===================" << endl;
	}
}
