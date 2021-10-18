#include <stdio.h>
#include <windows.h>

void main()
{
    HANDLE hPipe;
    LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
    //TEXT("\\\\WANDERER\\pipe\\MyPipe");
    DWORD iBytesToWrite;
    char buff[] = "A message from the client";
    // hPipe = CreateFile(
    //     lpPipeName,    // имя канала
    //     GENERIC_READ | // чтение и запись в канал
    //         GENERIC_WRITE,
    //     0,             // нет разделяемых операций
    //     NULL,          // защита по умолчанию
    //     OPEN_EXISTING, // открытие существующего канала
    //     0,             // атрибуты по умолчанию
    //     NULL);         // нет шаблона атрибутов
    // WriteFile(hPipe, buff, strlen(buff), &iBytesToWrite, NULL);
    CallNamedPipe(
        lpPipeName,
        buff,
        26,
        NULL,
        0,
        NULL,
        10);
    CloseHandle(hPipe);
}