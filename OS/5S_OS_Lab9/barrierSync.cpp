#include <windows.h>
#include <stdio.h>
#include <process.h>

void thread0(void *);
void thread1(void *);
int sh = 0;
int flag[2] = {1, 1};

int main()
{
    _beginthread(thread0, 0, NULL);
    _beginthread(thread1, 0, NULL);
    while (flag[0] || flag[1])
        ;
    printf("%i\n", sh);
    return 0;
}

void thread0(void *ingored)
{
    int i = 0;
    for (; i < 100; i++, sh++)
        Sleep(10);

    flag[0] = 0;
}

void thread1(void *ingored)
{
    int i = 0;
    for (; i < 100; i++, sh += 2)
        Sleep(10);

    flag[1] = 0;
}