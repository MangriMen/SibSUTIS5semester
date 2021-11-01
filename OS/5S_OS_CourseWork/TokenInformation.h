#pragma once
#include <comdef.h>
#define MAX_NAME 256

BOOL GetLogonFromToken(HANDLE hToken, _bstr_t &strUser, _bstr_t &strdomain)
{
    DWORD dwSize = MAX_NAME;
    BOOL bSuccess = FALSE;
    DWORD dwLength = 0;
    strUser = "";
    strdomain = "";
    PTOKEN_USER ptu = NULL;
    //Verify the parameter passed in is not NULL.
    if (NULL == hToken)
        goto Cleanup;

    if (!GetTokenInformation(
            hToken,      // handle to the access token
            TokenUser,   // get information about the token's groups
            (LPVOID)ptu, // pointer to PTOKEN_USER buffer
            0,           // size of buffer
            &dwLength    // receives required buffer size
            ))
    {
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            goto Cleanup;

        ptu = (PTOKEN_USER)HeapAlloc(GetProcessHeap(),
                                     HEAP_ZERO_MEMORY, dwLength);

        if (ptu == NULL)
            goto Cleanup;
    }

    if (!GetTokenInformation(
            hToken,      // handle to the access token
            TokenUser,   // get information about the token's groups
            (LPVOID)ptu, // pointer to PTOKEN_USER buffer
            dwLength,    // size of buffer
            &dwLength    // receives required buffer size
            ))
    {
        goto Cleanup;
    }
    SID_NAME_USE SidType;
    TCHAR lpName[MAX_NAME];
    TCHAR lpDomain[MAX_NAME];

    if (!LookupAccountSid(NULL, ptu->User.Sid, (LPTSTR)lpName, &dwSize, (LPTSTR)lpDomain, &dwSize, &SidType))
    {
        DWORD dwResult = GetLastError();
        if (dwResult == ERROR_NONE_MAPPED)
            _tcscpy_s(lpName, TEXT("NONE MAPPED"));
        else
        {
            _tprintf(TEXT("LookupAccountSid Error %u\n"), GetLastError());
        }
    }
    else
    {
        //_tprintf(TEXT("Current user is  %s\\%s\n"),
        //    lpDomain, lpName);
        strUser = lpName;
        strdomain = lpDomain;
        bSuccess = TRUE;
    }

Cleanup:

    if (ptu != NULL)
        HeapFree(GetProcessHeap(), 0, (LPVOID)ptu);
    return bSuccess;
}

HRESULT GetUserFromProcess(const DWORD procId, _bstr_t &strUser, _bstr_t &strdomain)
{
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, procId);
    if (hProcess == NULL)
        return E_FAIL;
    HANDLE hToken = NULL;

    if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
    {
        CloseHandle(hProcess);
        return E_FAIL;
    }
    BOOL bres = GetLogonFromToken(hToken, strUser, strdomain);

    CloseHandle(hToken);
    CloseHandle(hProcess);
    return bres ? S_OK : E_FAIL;
}