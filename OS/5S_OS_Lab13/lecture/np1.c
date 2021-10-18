#include <stdio.h>
#include <windows.h>

void main()
{
    HANDLE hPipe;
    LPTSTR lpPipeName = TEXT("\\\\.\\pipe\\MyPipe");
    char buff[255];
    DWORD iBytesToRead = 255, i;
    hPipe = CreateNamedPipe(
        lpPipeName,                 // имя канала
        PIPE_ACCESS_DUPLEX,         // чтение и запись из канала
        PIPE_TYPE_MESSAGE |         // передача сообщений по каналу
            PIPE_READMODE_MESSAGE | //режим чтения сообщений
            PIPE_WAIT,              // синхронная передача сообщений
        PIPE_UNLIMITED_INSTANCES,   //число экземпляров
        4096,                       // размер выходного буфера
        4096,                       // размер входного буфера
        NMPWAIT_USE_DEFAULT_WAIT,   // тайм-аут клиента
        NULL);                      // защита по умолчанию
    if (hPipe == INVALID_HANDLE_VALUE)
    {
        printf("CreatePipe failed: error code %d\n",
               (int)GetLastError());
        return;
    }
    if ((ConnectNamedPipe(hPipe, NULL)) == 0)
    {
        printf("client could not connect\n");
        return;
    }
    ReadFile(hPipe, buff, iBytesToRead, &iBytesToRead, NULL);
    for (i = 0; i < iBytesToRead; i++)
        printf("%c", buff[i]);
}
