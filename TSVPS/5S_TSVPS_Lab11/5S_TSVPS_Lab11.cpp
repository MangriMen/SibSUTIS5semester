#include <iostream>
#include "utils.hpp"

using namespace std;

int main() {
	cout << "Regular multiply: " << endl;
	multiplyWithPrint("3", "3", regularMultiply);
	//multiplyWithPrint("99999999999999999999", "99999999999999999999", regularMultiply);

	cout << "Fast multiply: " << endl;
	multiplyWithPrint("3", "3", fastMultiply);
	//multiplyWithPrint("99999999999999999999", "99999999999999999999", fastMultiply);

	cout << endl;
	cout << "Regular multiply" << endl;
	cout << "\tSum,Sub : " << regSumSub << endl;
	cout << "\tMult,Div: " << regMultDiv << endl;

	cout << endl;
	cout << "Fast multiply" << endl;
	cout << "\tSum,Sub : " << fastSumSub << endl;
	cout << "\tMult,Div: " << fastMultDiv << endl;

	return 0;
}