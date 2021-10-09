#include <iostream>
#include <windows.h>
#include <psapi.h>

using namespace std;

int main()
{
    DWORD pID;
    HANDLE pHndl;
    HMODULE *modHndls;
    DWORD b_alloc = 8, b_needed;
    char modName[MAX_PATH];

    pID = GetCurrentProcessId();
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