#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

size_t regularSumCounter = 0;
size_t regularMulCounter = 0;

size_t fastMulCounter = 0;
size_t fastSumCounter = 0;
map<size_t, size_t> fastDigitMult;
map<size_t, size_t> fastDigitMultOverflow;

size_t fastRecCounter = 0;

bool isMultiplyDebug = false;

int ctoi(const unsigned char& num) {
	return num - '0';
}

char itoc(const int& num) {
	return static_cast<unsigned char>(num + '0');
}

string paddedWithZerosToSizeFront(const string& str, size_t size) {
	if (str.size() >= size) {
		return str;
	}

	return string(size - str.size(), '0') + str;
}

string paddedWithZerosByNumberBack(const string& str, size_t size) {
	return str + string(size, '0');
}

tuple<const string, const string> splitIntoTwoSegments(const string& str, size_t size) {
	return make_tuple(str.substr(0, size), str.substr(size));
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

			regularSumCounter += 2;
			regularMulCounter += 3;
		}
		calculatedMult[i + second_.size()] += carry;
		regularSumCounter += 1;
	}

	reverse(calculatedMult.begin(), calculatedMult.end());

	string result("");
	for (const short& i : calculatedMult) {
		result += to_string(i);
	}
	result.erase(0, result[0] == '0');

	return result;
}

string add(const string& x, const string& y) {
	const size_t n = max(x.size(), y.size());
	unsigned short carry = 0;
	unsigned short sum_col;

	string xCopy = paddedWithZerosToSizeFront(x, n);
	string yCopy = paddedWithZerosToSizeFront(y, n);

	string result;
	for (size_t i = n - 1; i != numeric_limits<size_t>::max(); i--) {
		sum_col = ctoi(xCopy[i]) + ctoi(yCopy[i]) + carry;
		carry = sum_col / 10;
		result += to_string(sum_col % 10);
	}

	if (carry) {
		result += to_string(carry);
	}

	reverse(result.begin(), result.end());

	return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

string subtract(const string& x, const string& y) {
	const size_t n = max(x.size(), y.size());
	short diff;

	string xCopy = paddedWithZerosToSizeFront(x, n);
	string yCopy = paddedWithZerosToSizeFront(y, n);

	string result;
	for (long long i = n - 1; i >= 0; i--) {
		diff = ctoi(xCopy[i]) - ctoi(yCopy[i]);

		if (diff >= 0) {
			result += to_string(diff);
		}
		else {
			for (long long j = i - 1; j >= 0; j--) {
				xCopy[j] = itoc((ctoi(xCopy[j]) - 1) % 10);

				if (xCopy[j] != '9') {
					break;
				}
			}
			result += to_string(diff + 10);
		}
	}

	reverse(result.begin(), result.end());

	return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

size_t checkDigit(string a, string b) {
	return max(a.size(), b.size());
}

int checkOverflowCount(string a, string b, string c, string d) {
	int digitsOverflow = 0;

	if (add(a, b).size() > max(a.size(), b.size())) {
		digitsOverflow++;
	}

	if (add(c, d).size() > max(a.size(), b.size())) {
		digitsOverflow++;
	}

	return digitsOverflow;
}

string checkOverflow(string a, string b, string c, string d) {
	int digitsOverflow = checkOverflowCount(a, b, c, d);

	if (digitsOverflow == 1) {
		return "with 1 overflow";
	}
	else if (digitsOverflow == 2) {
		return "with 2 overflows";
	}
	else {
		return "without overflow";
	}
}

string fastMultiplyAction(const string& first, const string& second, size_t overflow = 0) {
	const size_t n = max(first.size(), second.size());
	const size_t k = (overflow > 0) ? 1 : (n >> 1);

	if (n == 1) {
		fastMulCounter++;
		return to_string(ctoi(first[0]) * ctoi(second[0]));
	}

	auto [a, b] = splitIntoTwoSegments(paddedWithZerosToSizeFront(first, n), k);
	auto [c, d] = splitIntoTwoSegments(paddedWithZerosToSizeFront(second, n), k);

	if (overflow > 0) {
		string a1b1 = (ctoi(a[0]) && ctoi(c[0])) ? paddedWithZerosByNumberBack("1", 2 * (n - 1)) : "0";

		string a2b1 = ctoi(c[0]) ? b : "0";
		string a1b2 = ctoi(a[0]) ? d : "0";
		string brackets = paddedWithZerosByNumberBack(add(a2b1, a1b2), (n - 1));

		string a2b2 = fastMultiplyAction(b, d);

		fastSumCounter += 3;

		return add(add(a1b1, brackets), a2b2);
	}

	size_t overflowCount = checkOverflowCount(a, b, c, d);

	string u = fastMultiplyAction(add(a, b), add(c, d), overflowCount);
	string v = fastMultiplyAction(a, c);
	string w = fastMultiplyAction(b, d);

	fastSumCounter += 2;

	if (overflowCount > 0) {
		fastDigitMultOverflow[checkDigit(a, b)]++;
	}

	fastDigitMult[checkDigit(a, b)]++;
	fastDigitMult[checkDigit(a, c)]++;
	fastDigitMult[checkDigit(b, d)]++;

	if (isMultiplyDebug) {

		cout
			<< "\n"
			<< "U" << fastRecCounter << ": " << "(" << a << " + " << b << ")" << "(" << c << " + " << d << ")" << " = " << add(a, b) << " * " << add(c, d)
			<< " (" << checkDigit(a, b) << "-bit " << checkOverflow(a, b, c, d) << ")" << "\n"
			<< "V" << fastRecCounter << ": " << a << " * " << c << " = " << v
			<< " (" << checkDigit(a, c) << "-bit " << checkOverflow(a, "0", c, "0") << ")" << "\n"
			<< "W" << fastRecCounter << ": " << b << " * " << d << " = " << w
			<< " (" << checkDigit(b, d) << "-bit " << checkOverflow(b, "0", d, "0") << ")" << "\n";
	}

	string uvwSub = subtract(u, add(v, w));

	fastSumCounter += 1;

	v = paddedWithZerosByNumberBack(v, 2 * (n - k));
	uvwSub = paddedWithZerosByNumberBack(uvwSub, (n - k));

	string result = add(add(v, w), uvwSub);

	fastSumCounter += 2;

	if (isMultiplyDebug) {
		cout
			<< "Re" << ": " << result << "\n";
		fastRecCounter++;
	}

	return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

string fastMultiply(const string& first, const string& second) {
	return fastMultiplyAction(first, second);
}

void multiplyWithPrint(string a, string b, string(*function)(const string&, const string&)) {
	cout << a << " * " << b << " = " << function(a, b) << endl;
}