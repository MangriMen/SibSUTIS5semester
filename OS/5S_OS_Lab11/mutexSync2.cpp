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
        WaitForSingleObject(hEvent2, INFINITE);
        if (counter % 2)
        {
            _stprintf(outStr, TEXT("Thread Boy 1\n"));
        }
        else
        {
            _stprintf(outStr, TEXT("Thread Boy 2\n"));
        }
        ReleaseMutex(hEvent1);
        Sleep(100);
        counter++;
    }

    return EXIT_SUCCESS;
}