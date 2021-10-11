#include <iostream>
#include <chrono>
#include <windows.h>

#pragma comment(lib, "libSync")
HANDLE hEvent1, hEvent2;
extern __declspec(dllimport) TCHAR outStr[256];

int main()
{
    hEvent1 = CreateSemaphore(NULL, 1, 1, TEXT("ThreadEvent1"));
    hEvent2 = CreateSemaphore(NULL, 1, 1, TEXT("ThreadEvent2"));

    while (true)
    {
        WaitForSingleObject(hEvent1, INFINITE);
        std::cout << outStr;
        ReleaseSemaphore(hEvent2, 1, NULL);
    }

    CloseHandle(hEvent1);
    CloseHandle(hEvent2);

    return EXIT_SUCCESS;
}