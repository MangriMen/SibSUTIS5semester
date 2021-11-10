#include <iostream>

extern "C"
{
    __declspec(dllexport) int myFunc(int demo)
    {
        return demo * demo;
    }
}
