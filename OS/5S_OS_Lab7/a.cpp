#include <iostream>
#include <windows.h>

using namespace std;

typedef void (*VoidReturnFunc)();

int main()
{
    HINSTANCE lib1 = LoadLibrary(TEXT("lib1.dll"));

    if (!lib1)
    {
        cerr << "Could not load dll 'lib1.dll'" << endl;
        return EXIT_FAILURE;
    }

    VoidReturnFunc GetTime = (VoidReturnFunc)GetProcAddress(lib1, "GetTime");
    GetTime();

    if (!GetTime)
    {
        FreeLibrary(lib1);
        cerr << "Could not find function 'GetTime'" << endl;
        return EXIT_FAILURE;
    }

    FreeLibrary(lib1);
    return EXIT_SUCCESS;
}