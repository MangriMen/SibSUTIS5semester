#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <tuple>
#include <bitset>
using namespace std;

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

char itoc(const int& num) {
    return static_cast<unsigned char>(num + '0');
}

int ctoi(const unsigned char& number) {
	return (number - '0');
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

    while (x.size() < n)
        x.insert(0, "0");

    while (y.size() < n)
        y.insert(0, "0");

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

string fastMultiply(string first, string second) {
    string x(first);
    string y(second);

    const size_t n = max(x.size(), y.size());

    if (n == 1) {
        return to_string(ctoi(x[0]) * ctoi(y[0]));
    }

    const size_t k = n >> 1;
    const string halfNeededZeroes = string(n - k, '0');

    x = paddedWithZerosToSizeFront(x, n);
    y = paddedWithZerosToSizeFront(y, n);

    auto [a, b] = splitIntoTwoSegments(x, k);
    auto [c, d] = splitIntoTwoSegments(y, k);

    string u = fastMultiply(add(a, b), add(c, d));
    string v = fastMultiply(a, c);
    string w = fastMultiply(b, d);

    string uvwSub = subtract(u, add(v, w));

    v = paddedWithZerosByNumberBack(v, 2 * (n - k));
    uvwSub = paddedWithZerosByNumberBack(uvwSub, (n - k));

    string result = add(add(v, w), uvwSub);

    return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
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
	callAndLogMultiply("12345", "2", fastMultiply);
	callAndLogMultiply("3", "3", fastMultiply);
	callAndLogMultiply("6463", "21315", fastMultiply);
	callAndLogMultiply("18", "23", fastMultiply);
	callAndLogMultiply("625", "625", fastMultiply);
	callAndLogMultiply("455689967848757865764", "87578121242346457455689967", fastMultiply);

	return 0;
}