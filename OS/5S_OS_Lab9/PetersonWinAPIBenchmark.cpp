#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <chrono>

using namespace std::chrono;

CRITICAL_SECTION cs;
bool flag[2];
int turn = 0;

int sh = 0;
bool isPeterson = false;

void EnterCriticalRegion(int threadId)
{
    flag[threadId] = true; // Флаг текущего потока
    turn = 1 - threadId;   // Флаг очереди исполнения
    while (turn == 1 - threadId && flag[1 - threadId])
        ;
}

void LeaveCriticalRegion(int threadId)
{
    flag[threadId] = false; // Сброс флага текущего потока
}

void ThreadPeterson(void *pParams)
{
    int counter = *((int *)pParams);
    while (counter)
    {
        EnterCriticalRegion(0);
        sh++;
        LeaveCriticalRegion(0);
        counter--;
    }
    _endthread();
}

void ThreadWinAPI(void *pParams)
{
    int counter = *((int *)pParams);
    while (counter)
    {
        EnterCriticalSection(&cs);
        sh++;
        LeaveCriticalSection(&cs);
        counter--;
    }
    _endthread();
}

int main()
{
    auto localStart = high_resolution_clock::now();
    auto localEnd = high_resolution_clock::now();

    int count = 1000;
    std::cout << "Enter test size number (1000 default)"
              << "\n";
    std::cin >> count;
    int countD = count * count;

    sh = 0;
    isPeterson = true;

    _beginthread(ThreadPeterson, 0, (int *)&count);

    localStart = high_resolution_clock::now();
    while (sh < countD)
    {
        EnterCriticalRegion(1);
        sh++;
        LeaveCriticalRegion(1);
    }
    localEnd = high_resolution_clock::now();

    std::cout
        << "Peterson time: "
        << duration_cast<microseconds>(localEnd - localStart).count() << " ms"
        << "\n";

    sh = 0;
    isPeterson = false;
    InitializeCriticalSection(&cs);

    _beginthread(ThreadWinAPI, 0, (int *)&count);

    localStart = high_resolution_clock::now();
    while (sh < countD)
    {
        EnterCriticalSection(&cs);
        sh++;
        LeaveCriticalSection(&cs);
    }
    localEnd = high_resolution_clock::now();
    DeleteCriticalSection(&cs);

    std::cout
        << "WinAPI time: "
        << duration_cast<microseconds>(localEnd - localStart).count() << " ms"
        << "\n";

    return 0;
}