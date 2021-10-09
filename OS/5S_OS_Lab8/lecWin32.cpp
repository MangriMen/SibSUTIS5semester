#include <windows.h>
#include <stdio.h>
typedef int (*fun)(char *, int *p);

int g(char *str, int *p)
{
    *p = 0;
    printf("%s\n", str);
    return 0;
}

int q = 1;

DWORD WINAPI Thread(void *pg)
{
    int counter = 0;
    while (q)
    {
        printf("child\n");
        Sleep(10);
        if (counter++ > 1000)
            break;
    }
    ((fun)pg)("thread_is_over!", &q);
    return 0;
}

int main(void)
{
    DWORD dwThreadId;
    CreateThread(
        NULL,         // аттрибуты безопасности по умолчанию
        0,            // размер стека потока по умолчанию
        Thread,       // функция потока
        g,            // аргумент функции потока
        0,            // флаги создания потока по умолчанию
        &dwThreadId); // возврат идентификатора потока
    while (q)
    {
        printf("parent\n", q);
        Sleep(10);
    }
    return 0;
}