#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>
#include <atlstr.h>
#include <vector>
#include <algorithm>
#include "TokenInformation.h"

using namespace std;

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors = 12;

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
    _tprintf(TEXT("%-34s%-20d%-20ws%3d%%\n"), proc.name, proc.PID, proc.ownerUsername, static_cast<int>(proc.CPU));
    // _tprintf(TEXT("%-74s%-10IuKb|%-10IuKb|%-10IuKb|%-10IuKb\n"), TEXT(""), proc.memoryUsage.PagefileUsage / 1024, proc.memoryUsage.PrivateUsage / 1024, proc.memoryUsage.QuotaNonPagedPoolUsage / 1024, proc.memoryUsage.WorkingSetSize / 1024);
}

bool processDataCompName(const PROCESS_DATA &a, const PROCESS_DATA &b)
{
    return _tcscmp(a.name, b.name) < 0;
}

bool processDataCPU(const PROCESS_DATA &a, const PROCESS_DATA &b)
{
    return a.CPU < b.CPU;
}

double getCurrentValue(HANDLE hProcess)
{
    FILETIME ftime, fsys, fuser;
    ULARGE_INTEGER now, sys, user;
    double percent;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&now, &ftime, sizeof(FILETIME));

    GetProcessTimes(hProcess, &ftime, &ftime, &fsys, &fuser);
    memcpy(&sys, &fsys, sizeof(FILETIME));
    memcpy(&user, &fuser, sizeof(FILETIME));
    percent = (sys.QuadPart - lastSysCPU.QuadPart) +
              (user.QuadPart - lastUserCPU.QuadPart);
    percent /= (now.QuadPart - lastCPU.QuadPart);
    percent /= numProcessors;
    lastCPU = now;
    lastUserCPU = user;
    lastSysCPU = sys;

    return percent * 100;
}

int main()
{
    DWORD cbReturned;
    DWORD cbAlloc = SHRT_MAX;
    DWORD *allPidS = new DWORD[cbAlloc];
    PROCESS_MEMORY_COUNTERS_EX memCounter;
    vector<PROCESS_DATA> processList;

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    numProcessors = sysInfo.dwNumberOfProcessors;

    FILETIME ftime;
    GetSystemTimeAsFileTime(&ftime);
    memcpy(&lastCPU, &ftime, sizeof(FILETIME));

    FILETIME fsys, fuser;
    GetProcessTimes(GetCurrentProcess(), &ftime, &ftime, &fsys, &fuser);
    memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
    memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));

    if (!EnumProcesses(allPidS, cbAlloc, &cbReturned))
    {
        cerr << "Could not call EnumProcesses" << endl;
        return EXIT_FAILURE;
    }

    bool isDebug = false;

    while (true)
    {
        system("cls");
        processList.clear();
        processList.shrink_to_fit();
        _tprintf(TEXT("%-34s%-20s%-20s%-20s\n"), TEXT("Name"), TEXT("PID"), TEXT("Username"), TEXT("Memory"));

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

                    temp.CPU = getCurrentValue(hProcess);

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

        sort(processList.begin(), processList.end(), processDataCompName);

        for (const auto &process : processList)
        {
            // if (!_tcscmp(process.name, TEXT("Discord.exe")))
            // {
            printProcessData(process);
            // }
        }

        Sleep(1000);
    }

    return EXIT_SUCCESS;
}