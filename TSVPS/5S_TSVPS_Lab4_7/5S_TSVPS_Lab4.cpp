#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <complex>
#include <tuple>
#include <algorithm>
#include "utils.h"

using namespace std;

vector<complex<double>> getDiscreteFourierTransform(const vector<double>& data) {
	if (data.size() == 0) {
		return vector<complex<double>>();
	}

	vector<complex<double>> out(data.size());
	complex<double> exp_result;
	const double reverseN = 1.0 / static_cast<double>(data.size());
	const double EXPR_PART = -2.0 * M_PI * reverseN;

	for (size_t k = 0; k < data.size(); k++)
	{
		for (size_t j = 0; j < data.size(); j++)
		{
			exp_result = exp(1i * EXPR_PART * static_cast<double>(k) * static_cast<double>(j));
			out[k] += data[j] * exp_result;
		}
		out[k] *= reverseN;
	}

	return out;
}

vector<double> getReverseDiscreteFourierTransform(const vector<complex<double>>& data) {
	if (data.size() == 0) {
		return vector<double>();
	}

	vector<double> out(data.size());
	complex<double> exp_result;
	const double reverseN = 1.0 / static_cast<double>(data.size());
	const double EXPR_PART = 2.0 * M_PI * reverseN;

	for (size_t k = 0; k < data.size(); k++)
	{
		for (size_t j = 0; j < data.size(); j++)
		{
			exp_result = exp(1i * EXPR_PART * static_cast<double>(k) * static_cast<double>(j));
			out[k] += (data[j] * exp_result).real();
		}
	}

	return out;
}

vector<complex<double>> getSemiFastFourierTransform(const vector<double>& data) {
	if (data.size() == 0) {
		return vector<complex<double>>();
	}

	size_t p1, p2;
	tie(p1, p2) = utils::getNumberDecompositionBy2(data.size());

	vector<vector<complex<double>>> temp1(p1, vector<complex<double>>(p1));
	vector<vector<complex<double>>> temp2(p1, vector<complex<double>>(p1));

	double reverseP1 = 1.0 / static_cast<double>(p1);
	double reverseP2 = 1.0 / static_cast<double>(p2);
	const double EXPR_PART = -2.0 * M_PI * reverseP1;

	for (size_t k1 = 0; k1 < p1; k1++) {
		for (size_t j2 = 0; j2 < p2; j2++) {
			for (size_t j1 = 0; j1 < p1; j1++) {
				temp1[k1][j2] += data[j2 + p2 * j1] * exp(1i * EXPR_PART * (static_cast<double>(j1) * static_cast<double>(k1)));
			}
			temp1[k1][j2] *= reverseP1;
		}
	}

	for (size_t k1 = 0; k1 < p1; k1++) {
		for (size_t k2 = 0; k2 < p2; k2++) {
			for (size_t j2 = 0; j2 < p2; j2++) {
				temp2[k1][k2] += temp1[k1][j2] * exp(1i * EXPR_PART * (static_cast<double>(j2) * (static_cast<double>(k1) + static_cast<double>(p1) * static_cast<double>(k2)) / static_cast<double>(p2)));
			}
			temp2[k1][k2] *= reverseP2;
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

	return out;
}

vector<double> getReverseSemiFastFourierTransform(const vector<complex<double>>& data) {
	if (data.size() == 0) {
		return vector<double>();
	}

	size_t p1, p2;
	tie(p1, p2) = utils::getNumberDecompositionBy2(data.size());

	vector<vector<complex<double>>> temp1(p1, vector<complex<double>>(p1));
	vector<vector<complex<double>>> temp2(p1, vector<complex<double>>(p1));

	double reverseP1 = 1.0 / static_cast<double>(p1);
	double reverseP2 = 1.0 / static_cast<double>(p2);
	const double EXPR_PART = 2.0 * M_PI * reverseP1;

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

	return out;
}

int rev(int num, int lg_n) {
	int res = 0;

	for (int i = 0; i < lg_n; ++i) {
		if (num & (1 << i)) {
			res |= 1 << (lg_n - 1 - i);
		}
	}

	return res;
}

vector<complex<double>> getFastFourierTransform(const vector<double>& data) {
	if (data.size() == 0) {
		return vector<complex<double>>();
	}

	vector<complex<double>> out;
	transform(data.begin(), data.end(), std::back_inserter(out), [](const double& e) { return complex<double>(e); });

	int lg_n = 0;
	while ((static_cast<unsigned long long>(1) << lg_n) < data.size()) {
		++lg_n;
	}

	for (int i = 0; i < data.size(); ++i) {
		if (i < rev(i, lg_n)) {
			swap(out[i], out[rev(i, lg_n)]);
		}
	}

	for (int len = 2; len <= data.size(); len <<= 1) {
		double ang = 2 * M_PI / len;

		complex<double> wlen(cos(ang), sin(ang));
		
		for (int i = 0; i < data.size(); i += len) {
			complex<double> w(1);
			for (int j = 0; j < len / 2; ++j) {
				complex<double> u = out[i + j];
				complex<double> v = out[i + j + len / 2] * w;
				out[i + j] = u + v;
				out[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}

	return out;
}

vector<double> getReverseFastFourierTransform(const vector<complex<double>>& data) {
	if (data.size() == 0) {
		return vector<double>();
	}

	vector<complex<double>> outComplex(data);

	int lg_n = 0;
	while ((static_cast<unsigned long long>(1) << lg_n) < data.size()) {
		++lg_n;
	}

	for (int i = 0; i < data.size(); ++i) {
		if (i < rev(i, lg_n)) {
			swap(outComplex[i], outComplex[rev(i, lg_n)]);
		}
	}

	for (int len = 2; len <= data.size(); len <<= 1) {
		double ang = -2 * M_PI / len;

		complex<double> wlen(cos(ang), sin(ang));
		
		for (int i = 0; i < data.size(); i += len) {
			complex<double> w(1);
			for (int j = 0; j < len / 2; ++j) {
				complex<double> u = outComplex[i + j];
				complex<double> v = outComplex[i + j + len / 2] * w;
				outComplex[i + j] = u + v;
				outComplex[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}

	for (int i = 0; i < data.size(); ++i) {
		outComplex[i] /= data.size();
	}

	vector<double> out;
	transform(outComplex.begin(), outComplex.end(), std::back_inserter(out), [](const complex<double>& e) { return e.real(); });

	return out;
}

#define N 16

int main() {
	srand(static_cast<unsigned int>(time(NULL)));

	vector<double> data(N, 0);
	vector<complex<double>> dataComplex(N, 0);

	for (size_t i = 0; i < N; i++)
	{
		data[i] = i * i;
		dataComplex[i] = data[i];
	}

	vector<complex<double>> discreteFourier = getDiscreteFourierTransform(data);
	vector<complex<double>> semiFastFourier = getSemiFastFourierTransform(data);
	vector<complex<double>> fastFourier = getFastFourierTransform(data);

	vector<double> reverseDiscrete = getReverseDiscreteFourierTransform(discreteFourier);
	vector<double> reverseSemiFast = getReverseSemiFastFourierTransform(semiFastFourier);
	vector<double> reverseFast = getReverseFastFourierTransform(fastFourier);

	utils::printArr(data, "Original");
	cout << endl;
	//utils::printArr(discreteFourier, "Discrete Fourier Transform:");
	//cout << endl;
	//utils::printArr(semiFastFourier, "SemiFast Fourier Transform:");
	//cout << endl;
	utils::printArr(reverseDiscrete, "Reverse Fourier: ");
	cout << endl;
	utils::printArr(reverseSemiFast, "Reverse SemiFast: ");
	cout << endl;
	utils::printArr(reverseFast, "Reverse Fast: ");
	cout << endl;

	utils::writeCSV(data, "data");
	utils::writeCSV(discreteFourier, "discrete");
	utils::writeCSV(semiFastFourier, "semiFast");
	utils::writeCSV(reverseDiscrete, "discreteReverse");
	utils::writeCSV(reverseSemiFast, "semiFastReverse");

	return 0;
}