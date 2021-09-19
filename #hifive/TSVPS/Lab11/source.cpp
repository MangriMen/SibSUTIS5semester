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

int ctoi(const char& number) {
	return (number - '0');
}

string fastMultiply(string first, string second) {
	long n = max(first.size(), second.size());
	n = (n & 1) ? n + 1 : n;
	const long k = n >> 1;

	first.insert(0, string(n - first.size(), '0'));
	second.insert(0, string(n - second.size(), '0'));

	const string aNumStr = first.substr(0, k);
	const string bNumStr = first.substr(k, first.size());
	const string cNumStr = second.substr(0, k);
	const string dNumStr = second.substr(k, second.size());

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

	return to_string(xy);
}

string regularMultiply(string first, string second) {
	vector<int> calculatedMult(first.size() + second.size(), 0);

	reverse(first.begin(), first.end());
	reverse(second.begin(), second.end());

	for (size_t i = 0; i < first.size(); ++i) {
		int carry = 0;

		for (size_t j = 0; j < second.size(); j++) {
			calculatedMult[i + j] += carry + ctoi(first[i]) * ctoi(second[j]);
			carry = calculatedMult[i + j] / 10;
			calculatedMult[i + j] %= 10;
		}

		calculatedMult[i + second.size()] += carry;
	}

	reverse(calculatedMult.begin(), calculatedMult.end());

	string result = "";
	for (const auto& i : calculatedMult) {
		result += to_string(i);
	}

	return (result[0] == '0') ? result.erase(0, 1) : result;
}

void callAndLogMultiply(string a, string b, string (*function)(string, string)) {
	cout << a << ", " << b << ": " << function(a, b) << endl;
}

int main() {
	cout << "Regular multiply: " << endl;
	callAndLogMultiply("12345", "2", regularMultiply);
	callAndLogMultiply("3", "3", regularMultiply);
	callAndLogMultiply("6463", "21315", regularMultiply);
	callAndLogMultiply("18", "23", regularMultiply);
	callAndLogMultiply("625", "625", regularMultiply);
	callAndLogMultiply("455689967848757865764", "87578121242346457455689967", regularMultiply);

	cout << endl << "Fast multiply: " << endl;
	callAndLogMultiply("3", "3", fastMultiply);
	callAndLogMultiply("18", "23", fastMultiply);

	return 0;
}