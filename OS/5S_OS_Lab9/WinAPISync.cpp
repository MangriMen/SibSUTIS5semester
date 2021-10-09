#include <windows.h>
#include <process.h>
#include <stdio.h>

CRITICAL_SECTION cs;
char sh[6];

#define CRT_SEC

void Thread(void *pParams)
{
    int counter = 0;
    while (1)
    {
#ifdef CRT_SEC
        EnterCriticalSection(&cs);
#endif
        if (counter % 2)
        {
            sh[0] = 'H';
            sh[1] = 'e';
            sh[2] = 'l';
            sh[3] = 'l';
            sh[4] = 'o';
            sh[5] = '\0';
        }
        else
        {
            sh[0] = 'B';
            sh[1] = 'y';
            sh[2] = 'e';
            sh[3] = '_';
            sh[4] = 'u';
            sh[5] = '\0';
        }
#ifdef CRT_SEC
        LeaveCriticalSection(&cs);
#endif
        counter++;
    }
}

int main(void)
{
#ifdef CRT_SEC
    InitializeCriticalSection(&cs);
#endif
    _beginthread(Thread, 0, NULL);
    while (1)
    {
#ifdef CRT_SEC
        EnterCriticalSection(&cs);
#endif
        printf("%s\n", sh);
#ifdef CRT_SEC
        LeaveCriticalSection(&cs);
#endif
    }
    return 0;
}
