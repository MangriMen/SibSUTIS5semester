#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstddef>
#include <bitset>
using namespace std;

#define ll long long

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

	bitset<sizeof(long)* CHAR_BIT> aBin(aNumStr);
	bitset<sizeof(long)* CHAR_BIT> bBin(bNumStr);
	bitset<sizeof(long)* CHAR_BIT> cBin(cNumStr);
	bitset<sizeof(long)* CHAR_BIT> dBin(dNumStr);

	const long a = static_cast<long>(aBin.to_ulong());
	const long b = static_cast<long>(bBin.to_ulong());
	const long c = static_cast<long>(cBin.to_ulong());
	const long d = static_cast<long>(dBin.to_ulong());

	const long u = (a + b) * (c + d);
	const long v = a * c;
	const long w = b * d;

	const ll xy = v * pow(2, 2 * k)
		+ (static_cast<ll>(u) - static_cast<ll>(v) - static_cast<ll>(w)) * pow(2, k)
		+ w;

	return xy * negativeMultiplier;
}

ll regularMultiply(long first, long second) {
	char negativeMultiplier = 1;

	if (first < 0 || second < 0) {
		negativeMultiplier = -1;
		first = abs(first);
		second = abs(second);
	}

	vector<ll> firstVec;
	vector<ll> secondVec;

	for (size_t i = first; i > 0; i /= 10) {
		firstVec.push_back(i % 10);
	}

	for (size_t i = second; i > 0; i /= 10) {
		secondVec.push_back(i % 10);
	}

	vector<unsigned ll> calculatedMult(firstVec.size() + secondVec.size(), 0);

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

	return stoll(result);
}

void callAndLogMultiply(ll a, ll b, ll (*function)(long, long)) {
	cout << a << ", " << b << ": " << function(a, b) << endl;
}

int main() {
	cout << "Regular multiply: " << endl;
	callAndLogMultiply(123155, 23151552, regularMultiply);
	callAndLogMultiply(3, 3, regularMultiply);
	callAndLogMultiply(6463, 21315, regularMultiply);
	callAndLogMultiply(18, 23, regularMultiply);
	callAndLogMultiply(625, 625, regularMultiply);

	cout << endl << "Fast multiply: " << endl;
	callAndLogMultiply(123155, 23151552, fastMultiply);
	callAndLogMultiply(3, 3, fastMultiply);
	callAndLogMultiply(6463, 21315, fastMultiply);
	callAndLogMultiply(18, 23, fastMultiply);
	callAndLogMultiply(625, 625, fastMultiply);

	return 0;
}