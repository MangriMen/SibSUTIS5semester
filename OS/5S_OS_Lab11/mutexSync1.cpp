#include <iostream>
#include <chrono>
#include <windows.h>
#include <atlstr.h>

#pragma comment(lib, "libSync")
HANDLE hEvent1, hEvent2;
extern __declspec(dllimport) TCHAR outStr[256];

int main()
{
    hEvent1 = CreateMutex(NULL, FALSE, TEXT("ThreadEvent1"));
    hEvent2 = CreateMutex(NULL, FALSE, TEXT("ThreadEvent2"));

    int counter = 0;
    while (true)
    {
        WaitForSingleObject(hEvent1, INFINITE);
        std::cout << outStr;
        ReleaseMutex(hEvent1);
    }

    CloseHandle(hEvent1);
    CloseHandle(hEvent2);

    return EXIT_SUCCESS;
}