#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

size_t regSumSub = 0;
size_t regMultDiv = 0;

size_t fastSumSub = 0;
size_t fast1bitMult = 0;
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

			regSumSub += 2;
			regMultDiv += 3;
		}
		calculatedMult[i + second_.size()] += carry;
		regSumSub += 1;
	}

	reverse(calculatedMult.begin(), calculatedMult.end());

	string result("");
	for (const short& i : calculatedMult) {
		result += to_string(i);
	}
	result.erase(0, result[0] == '0');

	return result;
}

string add(string x, string y) {
	const size_t n = max(x.size(), y.size());
	unsigned short carry = 0;
	unsigned short sum_col;
	string result;

	x = paddedWithZerosToSizeFront(x, n);
	y = paddedWithZerosToSizeFront(y, n);

	for (size_t i = n - 1; i != numeric_limits<size_t>::max(); i--) {
		sum_col = (x[i] - '0') + (y[i] - '0') + carry;
		carry = sum_col / 10;
		result.insert(0, to_string(sum_col % 10));
	}

	if (carry) {
		result.insert(0, to_string(carry));
	}

	return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

string subtract(string x, string y) {
	const size_t n = max(x.size(), y.size());
	short diff;
	string result;

	x = paddedWithZerosToSizeFront(x, n);
	y = paddedWithZerosToSizeFront(y, n);

	for (long long i = n - 1; i >= 0; i--) {
		diff = ctoi(x[i]) - ctoi(y[i]);

		if (diff >= 0) {
			result.insert(0, to_string(diff));
		}
		else {
			for (long long j = i - 1; j >= 0; j--) {
				x[j] = itoc((ctoi(x[j]) - 1) % 10);

				if (x[j] != '9') {
					break;
				}
			}
			result.insert(0, to_string(diff + 10));
		}
	}

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

string fastMultiplyAction(const string& first, const string& second, int overflow = 0) {
	string x(first);
	string y(second);

	const size_t n = max(x.size(), y.size());
	const size_t k = n >> 1;

	if (n == 1) {
		fast1bitMult += 1;
		return to_string(ctoi(x[0]) * ctoi(y[0]));
	}

	const string halfNeededZeroes = string(n - k, '0');

	x = paddedWithZerosToSizeFront(x, n);
	y = paddedWithZerosToSizeFront(y, n);

	auto [a, b] = splitIntoTwoSegments(x, k);
	auto [c, d] = splitIntoTwoSegments(y, k);

	string res;
	if (overflow >= 2) {
		string a1b1 = static_cast<bool>(stoll(a) * stoll(c)) ? paddedWithZerosByNumberBack("", 2 * (n - k)) : "0";
		string a2 = static_cast<bool>(stoll(c)) ? b : "0";
		string b2 = static_cast<bool>(stoll(a)) ? d : "0";
		string brackets = add(a2, b2);
		brackets = paddedWithZerosByNumberBack(brackets, (n - k));
		string a2b2 = fastMultiplyAction(b, d);
		fastDigitMultOverflow[checkDigit(x, y)]++;
		res = add(add(a1b1, brackets), a2b2);
		return res;
	}

	string u = fastMultiplyAction(add(a, b), add(c, d), checkOverflowCount(a, b, c, d));
	string v = fastMultiplyAction(a, c);
	string w = fastMultiplyAction(b, d);

	string uvwSub = subtract(u, add(v, w));

	fastSumSub += 4;

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

	fastDigitMult[checkDigit(a, b)]++;
	fastDigitMult[checkDigit(a, c)]++;
	fastDigitMult[checkDigit(b, d)]++;

	fastRecCounter++;

	v = paddedWithZerosByNumberBack(v, 2 * (n - k));
	uvwSub = paddedWithZerosByNumberBack(uvwSub, (n - k));

	string result = add(add(v, w), uvwSub);

	if (isMultiplyDebug) {
		cout
			<< "Re" << ": " << result << "\n";
	}

	return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

string fastMultiply(const string& first, const string& second) {
	return fastMultiplyAction(first, second);
}

void multiplyWithPrint(string a, string b, string(*function)(const string&, const string&)) {
	cout << a << " * " << b << " = " << function(a, b) << endl;
}