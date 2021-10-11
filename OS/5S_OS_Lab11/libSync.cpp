#include <iostream>
#include <string>
#include <windows.h>
#pragma data_seg(".M_TH")
extern __declspec(dllexport) TCHAR outStr[256] = {'\0'}; //инициализация обязательна
#pragma data_seg()
#pragma comment(linker, "/SECTION:.M_TH,RWS")

int main()
{
    return EXIT_SUCCESS;
}