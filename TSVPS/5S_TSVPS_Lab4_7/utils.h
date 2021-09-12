#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <complex>
#include <tuple>

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
			out << (point.real() >= 0 ? " " : "") << point.real() << " + " << (point.imag() >= 0 ? " " : "") << point.imag() << "i" << endl;
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

	tuple<size_t, size_t> getNumberDecompositionBy2(size_t number) {
		for (int i = sqrt(number); i <= number; ++i) {
			if (number % i == 0) {
				return { i, number / i };
			}
		}
	}
}
