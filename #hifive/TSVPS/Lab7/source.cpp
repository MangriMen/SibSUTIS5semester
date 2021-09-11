#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

namespace utils {
	string ReplaceAll(string str, const string& from, const string& to) {
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
		return str;
	}

	string dtos(double number, string delimiter = ".") {
		return ReplaceAll(to_string(number), ".", delimiter);
	}

	double func1(double x) {
		return (x * x * 2.0 - rand() % 1000000 * x);
	}

	void fillFunc(vector<double>& arr, size_t size) {
		arr.resize(size, 0);
		double point = 0;
		for (size_t i = 0; i < arr.size(); i++, point += 0.1)
		{
			arr[i] = func1(point);
		}
	}

	template <typename T>
	void printArr(const vector<T>& arr, string message = "", bool isInline = false) {
		stringstream out;

		if (message != "") {
			out << message;
		}

		if (!isInline) {
			out << endl;
		}

		out << setprecision(6) << fixed;
		for (const auto& i : arr) {
			out << i << " ";
		}

		out << endl;

		cout << out.str();
	}

	void printArr(const vector<complex<double>>& arr, string message = "", bool isInline = false) {
		stringstream out;

		if (message != "") {
			out << message;
		}

		if (!isInline) {
			out << endl;
		}

		out << setprecision(6) << fixed;
		for (const auto& point : arr) {
			out << "RE:" << (point.real() >= 0 ? " " : "") << point.real() << setw(6) << "IM:" << (point.imag() >= 0 ? " " : "") << point.imag() << endl;
		}

		cout << out.str();
	}

	void writeCSV(const vector<double>& arr, string filename) {
		ofstream out(filename + ".csv");

		if (!out.is_open()) {
			return;
		}

		for (const auto& i : arr) {
			string str = to_string(i) + "\n";
			str = ReplaceAll(str, ".", ",");
			out.write(str.c_str(), str.size());
		}

		out.close();
	}

	void writeCSV(const vector<complex<double>>& arr, string filename) {
		ofstream out(filename + ".csv");

		if (!out.is_open()) {
			return;
		}

		for (size_t i = 0; i < arr.size(); i++) {
			string fin = dtos(arr[i].real(), ",") + ";" + dtos(arr[i].imag(), ",");
			out << fin << endl;
		}

		out.close();
	}
}

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
	p1 = p2 = static_cast<size_t>(sqrt(data.size()));

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
	for (size_t k1 = 0, j = 0; k1 < p1; k1++) {
		for (size_t k2 = 0; k2 < p2; k2++, j++) {
			out[j] = temp2[k1][k2];
		}
	}

	return out;
}

vector<double> getReverseSemiFastFourierTransform(const vector<complex<double>>& data) {
	if (data.size() == 0) {
		return vector<double>();
	}

	size_t p1, p2;
	p1 = p2 = static_cast<size_t>(sqrt(data.size()));

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
	for (size_t k1 = 0, j = 0; k1 < p1; k1++) {
		for (size_t k2 = 0; k2 < p2; k2++, j++) {
			out[j] = temp2[k1][k2].real();
		}
	}

	return out;
}

vector<double> convolution(vector<double> a, vector<double> b) {
	size_t size_ = 0;
	vector<double> shortArr;
	vector<double> longArr;

	if (a.size() < b.size()) {
		shortArr = a;
		longArr = b;
	}
	else {
		shortArr = b;
		longArr = a;
	}
	size_ = shortArr.size() + longArr.size() - 1;

	vector<double> out(size_, 0);

	for (size_t k = 0; k < shortArr.size(); k++)
	{
		for (size_t l = 0; l < longArr.size(); l++)
		{
			out[l + k] += shortArr[k] * longArr[l];
		}
	}

	return out;
}

vector<double> convolutionDiscreteFourier(vector<double> a, vector<double> b) {
	size_t size_ = 0;
	vector<double> out(size_, 0);

	if (a.size() < b.size()) {
		size_ = b.size();
		a.resize(size_, 0.0);
	}
	else {
		size_ = a.size();
		b.resize(size_, 0.0);
	}

	vector<complex<double>> fourierA = getDiscreteFourierTransform(a);
	vector<complex<double>> fourierB = getDiscreteFourierTransform(b);

	vector<complex<double>> temp(size_, 0);
	for (size_t i = 0; i < size_; i++)
	{
		temp[i] = (2.0 * static_cast<double>(size_)) * (fourierA[i] * fourierB[i]);
	}

	out = getReverseDiscreteFourierTransform(temp);

	return out;
}

vector<double> convolutionSemiFastFourier(vector<double> a, vector<double> b) {
	size_t size_ = 0;
	vector<double> out(size_, 0);

	if (a.size() < b.size()) {
		size_ = b.size();
		a.resize(size_, 0.0);
	}
	else {
		size_ = a.size();
		b.resize(size_, 0.0);
	}

	vector<complex<double>> fourierA = getSemiFastFourierTransform(a);
	vector<complex<double>> fourierB = getSemiFastFourierTransform(b);

	vector<complex<double>> temp(size_, 0);
	for (size_t i = 0; i < size_; i++)
	{
		complex<double> mult = (fourierA[i] * fourierB[i]);
		temp[i] = (2.0 * static_cast<double>(size_)) * mult;
	}

	out = getReverseSemiFastFourierTransform(temp);

	return out;
}

#define N 1

int main()
{
	vector<double> dataA;
	vector<double> dataB;

	dataA = { 1, 2 };
	dataB = { 3, 4, 5 };

	vector<double> out = convolution(dataA, dataB);
	vector<double> outDF = convolutionDiscreteFourier(dataA, dataB);
	//vector<double> outSF = convolutionSemiFastFourier(dataA, dataB);


	utils::printArr(out, "Usually convolution:");
	cout << endl;
	utils::printArr(outDF, "Convolution with DFT:");
	//utils::printArr(outSF);
}
