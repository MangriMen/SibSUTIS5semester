#include <iostream>
#include "utils.hpp"

using namespace std;

int main() {
	isMultiplyDebug = true;
	cout << "Regular multiply: " << endl;
	multiplyWithPrint("3124", "3124", regularMultiply);
	//multiplyWithPrint("99999999999999999999", "99999999999999999999", regularMultiply);
	cout << "\n";

	cout << "Fast multiply: " << endl;
	multiplyWithPrint("9999999", "9999999", fastMultiply);
	//multiplyWithPrint("99999999999999999999", "99999999999999999999", fastMultiply);
	cout << "\n";

	cout << "Regular multiply" << endl;
	cout << "\tSum,Sub : " << regSumSub << endl;
	cout << "\tMult,Div: " << regMultDiv << endl;
	cout << "\n";

	cout << "Fast multiply" << endl;
	cout << "\t1-bit mult: " << fast1bitMult << endl;
	for (const auto& el : fastDigitMult) {
		if (el.first != 1) {
			cout << "\t" << el.first << "-bit mult: " << el.second;
			try {
				string out = " of them with overflow: " + to_string(fastDigitMultOverflow.at(el.first));
				cout << out;
			}
			catch (exception)
			{

			};
			cout << "\n";
		}
	}

	return 0;
}