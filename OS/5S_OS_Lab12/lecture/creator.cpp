#include <iostream>
#include <windows.h>

int main()
{
    HANDLE hFileMap;
    LPVOID lpMapView;
    char buff[16] = "Hello,students\0";
    hFileMap = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, 256, TEXT("MyCommonRegion"));
    lpMapView = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 256);
    CopyMemory(lpMapView, buff, 16);
    getchar();
    UnmapViewOfFile(lpMapView);
    CloseHandle(hFileMap);
    return 0;
}
