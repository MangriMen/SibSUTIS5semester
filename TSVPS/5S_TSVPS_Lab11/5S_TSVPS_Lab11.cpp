#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <bitset>
#include <complex>

using namespace std;

int ctoi(const char& num) {
	return num - '0';
}

char itoc(const int& num) {
	return num + '0';
}

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

string div2(const string& number) {
	string binaryNumber(number.size(), 0);
	short p = 0;
	short a = 0;

	for (size_t i = 0; i < number.size(); i++)
	{
		a = ctoi(number[i]) + p * 10;
		binaryNumber[i] = itoc(a >> 1);
		p = a % 2;
	}

	return binaryNumber;
}


bool isZero(const string& number) {
	return number.find_first_not_of("0") == string::npos;
}

string stobs(const string& number) {
	string out("");
	string number_(number);
	do {
		out += itoc(ctoi(number_[number_.size() - 1]) % 2);
		number_ = div2(number_);
	} while (!isZero(number_));

	reverse(out.begin(), out.end());
	return out;
}

string fastMultiply(const string& first, const string& second) {
	string xBinStr = stobs(first);
	string yBinStr = stobs(second);

	size_t n = max(xBinStr.size(), yBinStr.size());
	n = (n & 1) ? n + 1 : n;

	const size_t k = n >> 1;

	xBinStr.insert(0, string(n - xBinStr.size(), '0'));
	yBinStr.insert(0, string(n - yBinStr.size(), '0'));

	const string aNumStr = xBinStr.substr(0, k);
	const string bNumStr = xBinStr.substr(k, xBinStr.size());
	const string cNumStr = yBinStr.substr(0, k);
	const string dNumStr = yBinStr.substr(k, yBinStr.size());

	cout << endl << endl;
	cout << "UM " <<  ULLONG_MAX << endl;

	cout << endl << endl;

	cout << "a: " << aNumStr << endl;
	cout << "b: " << bNumStr << endl;
	cout << "c: " << cNumStr << endl;
	cout << "d: " << dNumStr << endl;

	const bitset<sizeof(size_t)* CHAR_BIT> bBin(bNumStr);
	const bitset<sizeof(size_t)* CHAR_BIT> aBin(aNumStr);
	const bitset<sizeof(size_t)* CHAR_BIT> cBin(cNumStr);
	const bitset<sizeof(size_t)* CHAR_BIT> dBin(dNumStr);

	const size_t a = aBin.to_ullong();
	const size_t b = bBin.to_ullong();
	const size_t c = cBin.to_ullong();
	const size_t d = dBin.to_ullong();

	cout << endl;
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl;
	cout << "d: " << d << endl;

	const size_t u = (a + b) * (c + d);
	const size_t v = a * c;
	const size_t w = b * d;

	cout << endl;
	cout << "u: " << u << endl;
	cout << "v: " << v << endl;
	cout << "w: " << w << endl;

	const size_t xy = v * static_cast<size_t>(pow(2, 2 * k))
		+ (u - v - w) * static_cast<size_t>(pow(2, k))
		+ w;

	cout << endl;

	return to_string(xy);
}

string regularMultiply(const string& first, const string& second) {
	vector<short> calculatedMult(first.size() + second.size(), 0);

	string first_(first);
	string second_(second);

	reverse(first_.begin(), first_.end());
	reverse(second_.begin(), second_.end());

	for (size_t i = 0; i < first_.size(); ++i) {
		short carry = 0;

		for (size_t j = 0; j < second_.size(); j++) {
			calculatedMult[i + j] += carry + ctoi(first_[i]) * ctoi(second_[j]);
			carry = calculatedMult[i + j] / 10;
			calculatedMult[i + j] %= 10;
		}

		calculatedMult[i + second_.size()] += carry;
	}

	reverse(calculatedMult.begin(), calculatedMult.end());

	string result("");
	for (const short& i : calculatedMult) {
		result += to_string(i);
	}
	result.erase(0, result[0] == '0');

	return result;
}

void MultiplyWithPrint(string a, string b, string(*function)(const string&, const string&)) {
	cout << a << " * " << b << " = " << function(a, b) << endl;
}

int main() {
	//cout << "Regular multiply: " << endl;
	//MultiplyWithPrint("99999999999999999999", "99999999999999999999", regularMultiply);
	//cout << "Fast multiply: " << endl;
	//MultiplyWithPrint("2", "2", fastMultiply);
	MultiplyWithPrint("99999999999999999999", "99999999999999999999", fastMultiply);

	return 0;
}