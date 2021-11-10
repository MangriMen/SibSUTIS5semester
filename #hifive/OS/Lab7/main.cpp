#include <iostream>
#include <windows.h>
using namespace std;

typedef int (*myFunc_t)(int);

int main()
{
    HINSTANCE dll = LoadLibrary("lab1");

    if (!dll)
    {
        return EXIT_FAILURE;
    }

    myFunc_t myFunc = (myFunc_t)GetProcAddress(dll, "myFunc");

    if (!myFunc)
    {
        FreeLibrary(dll);
        return EXIT_FAILURE;
    }

    cout << "Successfully loaded myFunc!" << endl;
    cout << myFunc(3) << endl;
    cout << myFunc(7) << endl;
    cout << myFunc(42) << endl;
    cout << "Successfully called myFunc!" << endl;

    FreeLibrary(dll);
    return 0;
}