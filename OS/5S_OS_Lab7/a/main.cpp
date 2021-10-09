#include <iostream>
#include <vector>
#include <windows.h>
#include <psapi.h>
#include <atlstr.h>

using namespace std;

int main()
{
    DWORD pID;
    HANDLE pHndl;
    HMODULE *modHndls;
    DWORD b_alloc = 8, b_needed;
    char modName[MAX_PATH];

    DWORD cbReturned;
    DWORD cbAlloc = INT_MAX;
    DWORD *allPidS = new DWORD[cbAlloc];

    if (!EnumProcesses(allPidS, cbAlloc, &cbReturned))
    {
        cerr << "Could not call EnumProcesses" << endl;
        return EXIT_FAILURE;
    }

    pID = GetCurrentProcessId();
    TCHAR procName[MAX_PATH];
    TCHAR progName[256];
    _stprintf(progName, TEXT("%s"), TEXT("prog1.exe"));
    for (DWORD i = 0; i < cbReturned / sizeof(DWORD); i++)
    {
        DWORD dwProcessId = allPidS[i];
        if (dwProcessId == 0 || dwProcessId == 8)
        {
            continue;
        }
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
        GetModuleBaseName(hProcess, NULL, procName, MAX_PATH);
        CloseHandle(hProcess);
        if (!_tcscmp(procName, progName))
        {
            pID = dwProcessId;
        }
    }

    pHndl = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    while (true)
    {
        modHndls = (HMODULE *)malloc(b_alloc);

        EnumProcessModules(pHndl, modHndls, b_alloc, &b_needed);
        cout << "PID:" << pID << " HANDLE:" << pHndl << endl;
        cout << "ALLOC:" << b_alloc << " NEED:" << b_needed << endl;
        if (b_alloc >= b_needed)
            break;
        else
        {
            free(modHndls);
            b_alloc = b_needed;
        }
    }
    for (int i = 0; i < b_needed / sizeof(DWORD); i++)
    {
        GetModuleBaseName(pHndl, modHndls[i],
                          (LPTSTR)modName, sizeof(modName));
        cout << "HANDLE:" << modHndls[i] << "\tBASENAME:" << modName;
        GetModuleFileName(modHndls[i], (LPTSTR)modName,
                          sizeof(modName));
        cout << "\tFILENAME:" << modName << endl;
    }

    return 0;
}