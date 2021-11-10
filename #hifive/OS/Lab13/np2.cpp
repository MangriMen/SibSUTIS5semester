#include <iostream>
#include <stdio.h>
#include <windows.h>
using namespace std;

void main()
{
    LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
    DWORD iBytesToWrite;

    HANDLE hPipe = CreateFile(
        lpPipeName,                   // имя канала
        GENERIC_READ | GENERIC_WRITE, // чтение и запись в канал
        0,                            // нет разделяемых операций
        NULL,                         // защита по умолчанию
        OPEN_EXISTING,                // открытие существующего канала
        0,                            // атрибуты по умолчанию
        NULL);                        // нет шаблона атрибутов

    string message = "";
    while (message != "!exit")
    {
        cin >> message;
        WriteFile(hPipe, message.c_str(), strlen(message.c_str()), &iBytesToWrite, NULL);
    }

    CloseHandle(hPipe);
}
