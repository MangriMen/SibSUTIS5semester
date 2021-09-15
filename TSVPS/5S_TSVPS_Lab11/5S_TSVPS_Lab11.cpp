#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

string itobs(int number) {
	string binaryNumber = "";

	if (number) {
		do {
			binaryNumber += std::to_string(number % 2);
		} while (number /= 2);
		reverse(binaryNumber.begin(), binaryNumber.end());
	}

	return binaryNumber;
}

long long fastMultiply(long first, long second) {
	char negativeMultiplier = 1;

	if (first < 0 || second < 0) {
		negativeMultiplier = -1;
		first = abs(first);
		second = abs(second);
	}

	string xBinStr = itobs(first);
	string yBinStr = itobs(second);

	long n = max(xBinStr.size(), yBinStr.size());
	n = (n & 1) ? n + 1 : n;
	
	const long k = n >> 1;

	xBinStr.insert(0, string(n - xBinStr.size(), '0'));
	yBinStr.insert(0, string(n - yBinStr.size(), '0'));

	const string aNumStr = xBinStr.substr(0, k);
	const string bNumStr = xBinStr.substr(k, xBinStr.size());
	const string cNumStr = yBinStr.substr(0, k);
	const string dNumStr = yBinStr.substr(k, yBinStr.size());

	const bitset<sizeof(long)* CHAR_BIT> bBin(bNumStr);
	const bitset<sizeof(long)* CHAR_BIT> aBin(aNumStr);
	const bitset<sizeof(long)* CHAR_BIT> cBin(cNumStr);
	const bitset<sizeof(long)* CHAR_BIT> dBin(dNumStr);

	const long a = static_cast<long>(aBin.to_ulong());
	const long b = static_cast<long>(bBin.to_ulong());
	const long c = static_cast<long>(cBin.to_ulong());
	const long d = static_cast<long>(dBin.to_ulong());

	const long u = (a + b) * (c + d);
	const long v = a * c;
	const long w = b * d;

	const long long xy = v * pow(2, 2 * k)
		+ (static_cast<long long>(u)
			- static_cast<long long>(v)
			- static_cast<long long>(w)) * pow(2, k)
		+ w;

	return xy * negativeMultiplier;
}

long long regularMultiply(long first, long second) {
	char negativeMultiplier = 1;

	if (first < 0 || second < 0) {
		negativeMultiplier = -1;
		first = abs(first);
		second = abs(second);
	}

	vector<long long> firstVec;
	vector<long long> secondVec;

	for (size_t i = first; i > 0; i /= 10) {
		firstVec.push_back(i % 10);
	}

	for (size_t i = second; i > 0; i /= 10) {
		secondVec.push_back(i % 10);
	}

	vector<long long> calculatedMult(firstVec.size() + secondVec.size(), 0);

	for (size_t i = 0; i < firstVec.size(); ++i) {
		long carry = 0;

		for (size_t j = 0; j < secondVec.size(); j++) {
			calculatedMult[i + j] += carry + firstVec[i] * secondVec[j];
			carry = calculatedMult[i + j] / 10;
			calculatedMult[i + j] %= 10;
		}

		calculatedMult[i + secondVec.size()] += carry;
	}

	reverse(calculatedMult.begin(), calculatedMult.end());

	string result = "";
	for (const auto& i : calculatedMult) {
		result += to_string(i);
	}

	return stoll(result) * negativeMultiplier;
}

void MultiplyWithPrint(long long a, long long b, long long (*function)(long, long)) {
	cout << a << " * " << b << " = " << function(a, b) << endl;
}

int main() {
	cout << "Regular multiply: " << endl;
	MultiplyWithPrint(2, 2, regularMultiply);
	MultiplyWithPrint(75, 82, regularMultiply);
	MultiplyWithPrint(INT_MAX, INT_MAX, regularMultiply);
	MultiplyWithPrint(10, -10, regularMultiply);
	
	cout << endl;

	cout << "Fast multiply: " << endl;
	MultiplyWithPrint(2, 2, fastMultiply);
	MultiplyWithPrint(75, 82, fastMultiply);
	MultiplyWithPrint(INT_MAX, INT_MAX, fastMultiply);
	MultiplyWithPrint(10, -10, fastMultiply);

	return 0;
}