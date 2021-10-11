#include <iostream>
#include <chrono>
#include <windows.h>
#include <atlstr.h>

#pragma comment(lib, "libSync")
HANDLE hEvent1, hEvent2;
extern __declspec(dllimport) TCHAR outStr[256];

int main()
{
    hEvent1 = CreateSemaphore(NULL, 1, 1, TEXT("ThreadEvent1"));
    hEvent2 = CreateSemaphore(NULL, 1, 1, TEXT("ThreadEvent2"));

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
        ReleaseSemaphore(hEvent1, 1, NULL);
        counter++;
        Sleep(100);
    }

    CloseHandle(hEvent1);
    CloseHandle(hEvent2);

    return EXIT_SUCCESS;
}