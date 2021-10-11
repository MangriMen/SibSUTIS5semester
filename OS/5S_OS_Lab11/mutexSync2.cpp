#include <iostream>
#include <chrono>
#include <windows.h>
#include <atlstr.h>

#pragma comment(lib, "libSync")
HANDLE hEvent1, hEvent2;
extern __declspec(dllimport) TCHAR outStr[256];

int main()
{
    hEvent1 = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("ThreadEvent1"));
    hEvent2 = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("ThreadEvent2"));

    int counter = 0;
    while (true)
    {
        WaitForSingleObject(hEvent1, INFINITE);
        if (counter % 2)
        {
            _stprintf(outStr, TEXT("Thread Boy 1\n"));
        }
        else
        {
            _stprintf(outStr, TEXT("Thread Boy 2\n"));
        }
        Sleep(100);
        ReleaseMutex(hEvent1);
        counter++;
    }

    CloseHandle(hEvent1);
    CloseHandle(hEvent2);

    return EXIT_SUCCESS;
}