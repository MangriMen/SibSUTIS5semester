#include <windows.h>
#include <stdio.h>
#include <process.h>

bool flag[3];
int turn = 0;
int sh = 0;

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

void thread0(void *ignored)
{
    int i = 0;
    for (; i < 100; i++)
    {
        EnterCriticalRegion(0); //while(turn);
        sh++;                   //критическая область
        LeaveCriticalRegion(0); //turn=1;
        Sleep(10);              //некритическая область
    }
    flag[0] = 0;
}
void thread1(void *ignored)
{
    int i = 0;
    for (; i < 100; i++)
    {
        EnterCriticalRegion(1); //while(!turn);
        sh += 2;                //критическая область
        LeaveCriticalRegion(1); //turn=0;
        Sleep(10);              //Sleep(10000); //некритическая область
    }
    flag[1] = 0;
}

int main()
{
    _beginthread(thread0, 0, NULL);
    _beginthread(thread1, 0, NULL);
    while (sh < 300)
    {
        EnterCriticalRegion(2);
        printf("%i\n", sh);
        LeaveCriticalRegion(2);
    }
    printf("%i\n", sh);
    return 0;
}