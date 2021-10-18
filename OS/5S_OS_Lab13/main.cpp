#include <iostream>
#include <windows.h>
#include <atlstr.h>

using namespace std;

constexpr DWORD bufferSize = 4096;

void main()
{
    srand(time(NULL));
    LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
    char buff[bufferSize];
    DWORD bytesRead = 0;

    HANDLE hPipe = CreateNamedPipe(
        lpPipeName,                 // имя канала
        PIPE_ACCESS_DUPLEX,         // чтение и запись из канала
        PIPE_TYPE_MESSAGE |         // передача сообщений по каналу
            PIPE_READMODE_MESSAGE | //режим чтения сообщений
            PIPE_WAIT,              // синхронная передача сообщений
        PIPE_UNLIMITED_INSTANCES,   //число экземпляров
        bufferSize,                 // размер выходного буфера
        bufferSize,                 // размер входного буфера
        NMPWAIT_USE_DEFAULT_WAIT,   // тайм-аут клиента
        NULL);                      // защита по умолчанию

    if (hPipe == INVALID_HANDLE_VALUE)
    {
        cerr << "CreatePipe failed. Error code: " << GetLastError() << "\n";
        return;
    }

    while (true)
    {
        _stprintf(buff, TEXT("kek"));
        cout << "Trying to connect...: ";
        if (WaitNamedPipe(lpPipeName, rand() % 100 + 10))
        {
            cout << "Success"
                 << "\n";
            HANDLE hPipeOut = CreateFile(
                lpPipeName,    // имя канала
                GENERIC_READ | // чтение и запись в канал
                    GENERIC_WRITE,
                0,             // нет разделяемых операций
                NULL,          // защита по умолчанию
                OPEN_EXISTING, // открытие существующего канала
                0,             // атрибуты по умолчанию
                NULL);         // нет шаблона атрибутов
            WriteFile(hPipeOut, "KEK", strlen("KEK"), &bytesRead, NULL);
            // CallNamedPipe(
            //     lpPipeName,
            //     "kek",
            //     bufferSize,
            //     buff,
            //     bufferSize,
            //     &bytesRead,
            //     10);
            CloseHandle(hPipeOut);

            cout << "\n";
        }
        else
        {
            ConnectNamedPipe(hPipe, NULL);

            cout << "Error"
                 << "\n";

            ReadFile(hPipe, buff, bufferSize, &bytesRead, NULL);
            cout << "Message: ";
            for (DWORD i = 0; i < bytesRead; i++)
                printf("%c", buff[i]);
            cout << "\n";
            DisconnectNamedPipe(hPipe);
        }
    }

    // if ((ConnectNamedPipe(hPipe, NULL)) == 0)
    // {
    //     printf("client could not connect\n");
    //     return;
    // }
    // ReadFile(hPipe, buff, iBytesToRead, &iBytesToRead, NULL);
    // for (i = 0; i < iBytesToRead; i++)
    //     printf("%c", buff[i]);
}
