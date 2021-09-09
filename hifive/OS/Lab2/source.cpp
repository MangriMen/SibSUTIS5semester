#include <windows.h>
#include <iostream>
#include <string>
#include <atlstr.h>
#include <fileapi.h>

using namespace std;

int main() {
    CString winDir;
    CString winTempDir;
    SYSTEM_INFO systemInfo;
    MEMORYSTATUSEX memoryInfo;
    size_t temp;
    temp = GetWindowsDirectory(winDir.GetBuffer(MAX_PATH), MAX_PATH);
    GetTempPath(MAX_PATH, winTempDir.GetBuffer(MAX_PATH));
    GetSystemInfo(&systemInfo);
    GlobalMemoryStatusEx(&memoryInfo);
    _tprintf(_T("%s\n"), (LPCTSTR)winDir);
    _tprintf(_T("%s\n"), (LPCTSTR)winTempDir);
    _tprintf(_T("NumberOfProcessors: %u\n"), systemInfo.dwNumberOfProcessors);
    _tprintf(_T("ProcessorArchitecture: %u\n"), systemInfo.wProcessorArchitecture);
    _tprintf(_T("MinimumApplicationAddress: %lp\n"), (LPCTSTR)systemInfo.lpMinimumApplicationAddress);
    _tprintf(_T("MaximumApplicationAddress: %lp\n"), (LPCTSTR)systemInfo.lpMaximumApplicationAddress);
    _tprintf(_T("Memory phys: %u \n"), memoryInfo.ullAvailPhys);
    _tprintf(_T("Memory virtual: %u \n"), memoryInfo.ullAvailVirtual);
    return 0;
}