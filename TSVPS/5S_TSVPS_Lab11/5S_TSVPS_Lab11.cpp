#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstddef>
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

long long fastMultiply(unsigned char x, unsigned char y) {
	string a = itobs(x);
	string b = itobs(y);

	int n = a.size() > b.size() ? a.size() : b.size();

	cout << a << "   " << a.size();

	long long result(0);

	//// x = 2
	//// a = 1 b = 0
	//// 0 10

	//cout << endl;
	return result;
}

long long regularMultiply(long firstNumber, long secondNumber) {
	vector<long long> firstNumberVec;
	vector<long long> secondNumberVec;

	for (size_t i = firstNumber; i > 0; i /= 10) {
		firstNumberVec.push_back(i % 10);
	}

	for (size_t i = secondNumber; i > 0; i /= 10) {
		secondNumberVec.push_back(i % 10);
	}

	vector<long long> calculatedMult(firstNumberVec.size() + secondNumberVec.size(), 0);

	for (size_t i = 0; i < secondNumberVec.size(); ++i) {
		int carry = 0;

		for (size_t j = 0; j < firstNumberVec.size(); j++) {
			calculatedMult[i + j] += carry + firstNumberVec[i] * secondNumberVec[j];
			carry = calculatedMult[i + j] / 10;
			calculatedMult[i + j] %= 10;
		}

		calculatedMult[i + secondNumberVec.size()] += carry;
	}

	reverse(calculatedMult.begin(), calculatedMult.end());

	string result = "";
	for (const auto& i : calculatedMult) {
		result += to_string(i);
	}

	return stoll(result);
}

int main() {
	cout << "Regular multiply: " << endl;

	cout << "34, 17: " << regularMultiply(34, 17) << endl;
	cout << "3, 3: " << regularMultiply(3, 3) << endl;
	cout << "20, 20: " << regularMultiply(20, 20) << endl;
	cout << "36, 21: " << regularMultiply(21, 36) << endl;

	cout << "Fast multiply: " << endl;

	/*cout << "34, 17: " << fastMultiply(34, 17) << endl;
	cout << "36, 21: " << fastMultiply(21, 36) << endl;
	cout << "20, 20: " << fastMultiply(20, 20) << endl;*/
	//cout << "3, 3: " << fastMultiply(255, 3) << endl;
	
	fastMultiply(8, 3);

	return 0;
}
