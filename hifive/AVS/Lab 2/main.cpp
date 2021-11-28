#include <math.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>

#define MHz 3600.000

using namespace std;
using namespace std::chrono;

struct Comma final : std::numpunct<char>
{
	char do_decimal_point() const override { return ','; }
};

int64_t fact(int64_t upTo)
{
	int64_t result = 1;

	while (upTo > 0)
	{
		result *= upTo;
		upTo--;
	}

	return result;
}

void logInfo(int i, duration<double> duration_temp, duration<double> duration_t, string functionName)
{
	const double absError = abs(i / (MHz * 1000 * 1000000) - duration_t.count() / i);
	double RelativeError = absError / (duration_t.count() / i);
	double TaskPerf = 100.0 - RelativeError;

	cout.precision(8);
	cout.imbue(std::locale(std::locale::classic(), new Comma));
	cout << endl
		 << endl
		 << fixed;

	cout << ("Task:;" + functionName) << endl;
	cout << "OpType:;int64_t (long long)" << endl;
	cout << "Opt:;None" << endl;
	cout << "InsCount:;" << i << endl;
	cout << "Timer:;now(), lib chrono" << endl;
	cout << "Time:;" << duration_temp.count() << endl;
	cout << "LNum:;1" << endl;
	cout << "AvTime:;" << duration_t.count() / i << endl;
	cout << "AbsError:;" << absError << endl;
	cout << "RelError:;" << RelativeError << "%" << endl;
	cout << "TaskPerf:;" << TaskPerf << endl;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	setlocale(LC_ALL, "EN");

	const int TEST_NUMBER = 1000;

	for (int count = 0; count < 3; ++count)
	{
		auto start_temp = high_resolution_clock::now();
		auto stop_temp = high_resolution_clock::now();

		auto start = high_resolution_clock::now();
		string functionName = "default";
		int i = 1;

		if (argc > 1)
		{
			i = atoi(argv[1]);
		}

		while (i-- > 1)
		{
			start_temp = high_resolution_clock::now();
			switch (count)
			{
			case 0:
				fact(TEST_NUMBER);
				functionName = "factorial";
				break;
			case 1:
				powf(TEST_NUMBER + 0.1, TEST_NUMBER + 0.1);
				functionName = "powf";
				break;
			case 2:
				log(TEST_NUMBER);
				functionName = "log";
				break;
			}
			stop_temp = high_resolution_clock::now();
		}

		auto stop = high_resolution_clock::now();
		duration<double> duration_temp = duration_cast<microseconds>(stop_temp - start_temp);
		duration<double> duration_t = duration_cast<microseconds>(stop - start);

		logInfo(atoi(argv[1]), duration_temp, duration_t, functionName);
	}

	return 0;
}
