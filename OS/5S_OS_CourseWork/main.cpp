#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>
#include <atlstr.h>
#include <vector>
#include <algorithm>
#include "TokenInformation.h"
#include "CPUusage.h"

using namespace std;

typedef struct process_t
{
    TCHAR name[MAX_PATH] = {'\0'};
    DWORD PID = 0;
    BSTR ownerUsername;
    PROCESS_MEMORY_COUNTERS_EX memoryUsage;
    double CPU = 0;
} PROCESS_DATA;

void printProcessData(const PROCESS_DATA &proc)
{
    _tprintf(TEXT("%-42s%-20d%-20ws%.2f%%%20Iu K\n"), proc.name, proc.PID, proc.ownerUsername, proc.CPU, proc.memoryUsage.WorkingSetSize / 1024);
}

bool processDataNameComp(const PROCESS_DATA &a, const PROCESS_DATA &b)
{
    return _tcscmp(a.name, b.name) < 0;
}

bool processDataNameCompI(const PROCESS_DATA &a, const PROCESS_DATA &b)
{
    return _tcscmp(a.name, b.name) < 0;
}

bool processDataCPUComp(const PROCESS_DATA &a, const PROCESS_DATA &b)
{
    return a.CPU < b.CPU;
}

bool processDataCPUCompI(const PROCESS_DATA &a, const PROCESS_DATA &b)
{
    return a.CPU < b.CPU;
}

bool processDataMemoryComp(const PROCESS_DATA &a, const PROCESS_DATA &b)
{
    return a.memoryUsage.WorkingSetSize < b.memoryUsage.WorkingSetSize;
}

bool processDataMemoryCompI(const PROCESS_DATA &a, const PROCESS_DATA &b)
{
    return a.memoryUsage.WorkingSetSize > b.memoryUsage.WorkingSetSize;
}

int main()
{
    DWORD cbReturned;
    DWORD cbAlloc = SHRT_MAX;
    DWORD *allPidS = new DWORD[cbAlloc];
    PROCESS_MEMORY_COUNTERS_EX memCounter;
    vector<PROCESS_DATA> processList;

    if (!EnumProcesses(allPidS, cbAlloc, &cbReturned))
    {
        cerr << "Could not call EnumProcesses" << endl;
        return EXIT_FAILURE;
    }

    bool isDebug = false;

    CPUusage cpuUsg(GetCurrentProcessId());

    while (true)
    {
        system("cls");
        processList.clear();
        processList.shrink_to_fit();
        _tprintf(TEXT("%-42s%-20s%-20s%-4s%20s\n"), TEXT("Name"), TEXT("PID"), TEXT("Username"), TEXT("CPU"), TEXT("Memory"));

        TCHAR procName[MAX_PATH] = {'\0'};
        for (DWORD i = 0, id = 0; i < cbReturned / sizeof(DWORD); i++)
        {
            DWORD dwProcessId = allPidS[i];
            if (dwProcessId == 0 || dwProcessId == 8)
            {
                continue;
            }
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessId);
            if (hProcess != NULL)
            {
                _stprintf(procName, TEXT("UNKNOWN"));
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
                    GetProcessMemoryInfo(hProcess, reinterpret_cast<PROCESS_MEMORY_COUNTERS *>(&memCounter), sizeof(memCounter));
                    PROCESS_DATA temp;
                    _tcscpy_s(temp.name, procName);
                    temp.PID = dwProcessId;
                    temp.ownerUsername = strUser.GetBSTR();
                    temp.memoryUsage = memCounter;

                    cpuUsg.setpid(dwProcessId);
                    for (size_t i = 0; i < 2; i++)
                    {
                        temp.CPU = (double)cpuUsg.get_cpu_usage();
                        Sleep(15);
                    }

                    processList.push_back(temp);
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

        sort(processList.begin(), processList.end(), processDataCPUCompI);

        for (const auto &process : processList)
        {
            // if (!_tcscmp(process.name, TEXT("Discord.exe")))
            // {
            printProcessData(process);
            // }
        }

        Sleep(1500);
    }

    return EXIT_SUCCESS;
}