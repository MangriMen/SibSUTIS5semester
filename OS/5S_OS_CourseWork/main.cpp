#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <atlstr.h>
#include "TokenInformation.h"

using namespace std;

int main()
{
    DWORD cbReturned;
    DWORD cbAlloc = SHRT_MAX;
    DWORD *allPidS = new DWORD[cbAlloc];

    if (!EnumProcesses(allPidS, cbAlloc, &cbReturned))
    {
        cerr << "Could not call EnumProcesses" << endl;
        return EXIT_FAILURE;
    }

    bool isDebug = false;

    TCHAR procName[MAX_PATH] = {'\0'};
    for (DWORD i = 0; i < cbReturned / sizeof(DWORD); i++)
    {
        DWORD dwProcessId = allPidS[i];
        if (dwProcessId == 0 || dwProcessId == 8)
        {
            continue;
        }
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessId);
        if (hProcess != NULL)
        {
            if (GetModuleBaseName(hProcess, NULL, procName, MAX_PATH))
            {
                HANDLE hToken = NULL;
                if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
                {
                    CloseHandle(hProcess);
                }
                _bstr_t strUser;
                _bstr_t strDomain;
                GetLogonFromToken(hToken, strUser, strDomain);
                _tprintf(TEXT("Name: %s PID: %d Username: %s\n"), procName, dwProcessId, strUser.GetBSTR());
            }
            else
            {
                if (isDebug)
                {
                    _tprintf(TEXT("Error: %d\n"), GetLastError());
                }
                CloseHandle(hProcess);
            }
            CloseHandle(hProcess);
        }
    }

    return EXIT_SUCCESS;
}