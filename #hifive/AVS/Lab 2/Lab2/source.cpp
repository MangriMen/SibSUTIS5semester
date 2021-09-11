#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <time.h>
#include <chrono>
#include <string>
using namespace std;
using namespace std::chrono;


uint64_t fact(uint64_t a) {
    uint64_t s = 1;

    while (--a) {
        s *= a + 1;
    }

    return s;
}

int functionLog(int number, int iterations, int type) {
    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        switch (type) {
            case 1: {
                fact(number);
            } break;
            case 2: {
                sin(number);
            } break;
            case 3: {
                log(number);
            } break;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    return duration.count();
}

int main() {
    srand(time(NULL));

    const int ITERATIONS = 10000;
    const int NUMBER = 15 + (rand() % 50);
    vector<int> averageTimings;

    cout << "Number to test: " << NUMBER << ".\n\n";
    cout << "factorial  | Elapsed time: " << functionLog(NUMBER, ITERATIONS, 1) * 0.001 << "ms.\n";
    cout << "sin        | Elapsed time: " << functionLog(NUMBER, ITERATIONS, 2) * 0.001 << "ms.\n";
    cout << "log        | Elapsed time: " << functionLog(NUMBER, ITERATIONS, 3) * 0.001 << "ms.\n";

    return 0;
}
