#include <windows.h>
#include <stdio.h>
#include <process.h>

void thread0(void *);
void thread1(void *);
int sh = 0;
//int flag[2] = { 1,1 };

int main()
{
    HANDLE h[2];
    h[0] = (HANDLE)_beginthread(thread0, 0, NULL);
    h[1] = (HANDLE)_beginthread(thread1, 0, NULL);
    //while (flag[0] || flag[1]);
    // WaitForSingleObject(h[1], INFINITE);
    WaitForMultipleObjects(2, h, TRUE, INFINITE);
    printf("%i\n", sh);
    return 0;
}

void thread0(void *ignored)
{
    int i = 0;
    for (; i < 100; i++, sh++)
        Sleep(10);
    //flag[0]=0;
}

void thread1(void *ignored)
{
    int i = 0;
    for (; i < 100; i++, sh += 2)
        Sleep(10);
    //flag[1]=0;
}
