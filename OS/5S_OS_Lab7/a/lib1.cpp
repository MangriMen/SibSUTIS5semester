#include <iostream>
#include <chrono>

using namespace std;

extern "C" __declspec(dllexport) void __stdcall GetTime()
{
    cout << "Hello World" << endl;
}