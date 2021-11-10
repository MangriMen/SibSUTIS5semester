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
#include <algorithm>
#include "../5S_TSVPS_Lab4_7/utils.h"

using namespace std;

size_t counter = 0;
size_t counterDF = 0;
size_t counterSF = 0;
size_t counterFF = 0;

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
			counterDF++;
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
			counterDF++;
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
				counterSF++;
			}
			temp1[k1][j2] *= reverseP1;
		}
	}

	for (size_t k1 = 0; k1 < p1; k1++) {
		for (size_t k2 = 0; k2 < p2; k2++) {
			for (size_t j2 = 0; j2 < p2; j2++) {
				temp2[k1][k2] += temp1[k1][j2] * exp(1i * EXPR_PART * (static_cast<double>(j2) * (static_cast<double>(k1) + static_cast<double>(p1) * static_cast<double>(k2)) / static_cast<double>(p2)));
				counterSF++;
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
				counterFF+=2;
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
				counterFF+=2;
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


vector<double> convolution(const vector<double>& x, const vector<double>& h) {
	if ((x.size() == 0) && (h.size() == 0)) {
		return vector<double>();
	}

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

size_t prepareArraysToConvolution(vector<double>& a, vector<double>& b) {
	size_t size_ = 0;

	if (a.size() < b.size()) {
		size_ = b.size();
		a.resize(size_, 0.0);
	}
	else {
		size_ = a.size();
		b.resize(size_, 0.0);
	}

	size_ *= 2;
	a.resize(size_, 0.0);
	b.resize(size_, 0.0);

	return size_;
}

vector<double> convolutionDiscreteFourier(vector<double> a, vector<double> b) {
	size_t size_ = prepareArraysToConvolution(a, b);
	vector<double> out(size_, 0);
	vector<complex<double>> temp(size_, 0);

	vector<complex<double>> fourierA = getDiscreteFourierTransform(a);
	vector<complex<double>> fourierB = getDiscreteFourierTransform(b);

	for (size_t i = 0; i < size_; i++)
	{
		temp[i] = static_cast<double>(size_) * fourierA[i] * fourierB[i];
		counterDF++;
	}

	out = getReverseDiscreteFourierTransform(temp);

	return out;
}

vector<double> convolutionSemiFastFourier(vector<double> a, vector<double> b) {
	size_t size_ = prepareArraysToConvolution(a, b);
	vector<double> out(size_, 0);
	vector<complex<double>> temp(size_, 0);

	vector<complex<double>> fourierA = getSemiFastFourierTransform(a);
	vector<complex<double>> fourierB = getSemiFastFourierTransform(b);

	for (size_t i = 0; i < size_; i++)
	{
		temp[i] = (static_cast<double>(size_)) * (fourierA[i] * fourierB[i]);
		counterSF++;
	}

	out = getReverseSemiFastFourierTransform(temp);
	
	return out;
}

vector<double> convolutionFastFourier(vector<double> a, vector<double> b) {
	size_t size_ = prepareArraysToConvolution(a, b);
	vector<double> out(size_, 0);
	vector<complex<double>> temp(size_, 0);

	vector<complex<double>> fourierA = getFastFourierTransform(a);
	vector<complex<double>> fourierB = getFastFourierTransform(b);

	for (size_t i = 0; i < size_; i++)
	{
		temp[i] = static_cast<double>(size_) * fourierA[i] * fourierB[i];
		counterFF++;
	}

	out = getReverseFastFourierTransform(temp);

	return out;
}

#define N 8

int main()
{
	vector<int> sizes = { 16, 64, 256, 1024 };

	for (const auto& i : sizes) {
		counter = 0;
		cout << "Size: " << i << endl << endl;
		vector<double> dataA(i, 0);
		vector<double> dataB(i, 0);

		vector<double> out;
		vector<double> outDF;
		vector<double> outSF;
		vector<double> outFF;

		for (size_t i = 0; i < dataA.size(); i++)
		{
			dataA[i] = i;
		}

		for (size_t i = 0; i < dataB.size(); i++)
		{
			dataB[i] = i;
		}

		out = convolution(dataA, dataB);
		outDF = convolutionDiscreteFourier(dataA, dataB);
		outSF = convolutionSemiFastFourier(dataA, dataB);
		outFF = convolutionFastFourier(dataA, dataB);

		//utils::printArr(out, "Usually convolution:");
		//cout << endl;
		//utils::printArr(outDF, "Convolution with DFT:");
		//cout << endl;
		//utils::printArr(outSF, "Convolution with SFFT:");

		cout << "Convolution: " << counter << endl;
		cout << "Convolution DFT: " << counterDF << endl;
		cout << "Convolution SFFT: " << counterSF << endl;
		cout << "Convolution FFT: " << counterFF << endl;
		cout << endl;
	}
}
