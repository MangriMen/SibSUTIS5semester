#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <iostream>
#include <windows.h>
#include <atlstr.h>
#include "clientRes.h"

LRESULT CALLBACK
DlgProc(HWND hDlg, UINT message, WPARAM wParam,
        LPARAM lParam);

BOOL CenterWindowOnDesktop(HWND hwndWindow);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    srand(time(NULL));
    MSG msg;
    DialogBox(hInstance, (LPCTSTR)IDD_DLGTEST, NULL,
              (DLGPROC)DlgProc);
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK
DlgProc(HWND hDlg, UINT message, WPARAM wParam,
        LPARAM lParam)
{
    TCHAR idText[100] = {'\0'};
    TCHAR strText[1024] = {'\0'};
    switch (message)
    {
    case WM_INITDIALOG:
        _stprintf(strText, TEXT("%d"), rand() % 10000 + 1);
        SetWindowText(hDlg, strText);
        CenterWindowOnDesktop(hDlg);
        return TRUE;
    case WM_COPYDATA:
    {
        HWND hwnd_idc_history = GetDlgItem(hDlg, IDC_HISTORY);
        PTCHAR inputMessage = (LPTSTR)(((PCOPYDATASTRUCT)lParam)->lpData);
        PTCHAR buf = new TCHAR[_tcslen(idText) + _tcslen(inputMessage)];

        GetWindowText(GetParent((HWND)wParam), idText, sizeof(idText) / sizeof(idText[0]));

        _stprintf(buf, TEXT("%s: %s\r\n\r"), (LPTSTR)idText, (LPTSTR)(((PCOPYDATASTRUCT)lParam)->lpData));
        SendMessage(hwnd_idc_history, EM_SETSEL, 0, -1);
        SendMessage(hwnd_idc_history, EM_SETSEL, -1, -1);
        SendMessageA(hwnd_idc_history, EM_REPLACESEL, 0, (LPARAM)(buf));

        delete[] buf;
    }
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_SEND:
            GetDlgItemText(hDlg, IDC_NAME, idText, sizeof(idText) / sizeof(idText[0]));
            GetDlgItemText(hDlg, IDC_MESSAGE, strText, sizeof(strText) / sizeof(strText[0]));
            HWND hWnd;
            COPYDATASTRUCT data;
            hWnd = FindWindow(TEXT("#32770"), (LPTSTR)idText);
            data.cbData = _tcslen(strText);
            data.lpData = strText;
            SendMessage(hWnd, WM_COPYDATA,
                        (WPARAM)GetFocus(),
                        (LPARAM)&data);
            return TRUE;
        case IDCANCEL:
            PostQuitMessage(0);
            return TRUE;
        }
        return TRUE;
    default:
        return FALSE;
    }
}

BOOL CenterWindowOnDesktop(HWND hwndWindow)
{
    int screenwidth, screenheight;
    int dlgwidth, dlgheight, x, y;
    RECT rect;

    /* Get Screen width and height */
    screenwidth = GetSystemMetrics(SM_CXSCREEN);
    screenheight = GetSystemMetrics(SM_CYSCREEN);

    /* Get Window rect top, left, right, bottom */
    GetWindowRect(hwndWindow, &rect);

    /* Calculate Window width and height */
    dlgwidth = rect.right - rect.left;
    dlgheight = rect.bottom - rect.top;

    /* Calculate Window left, top (x,y) */
    x = (screenwidth - dlgwidth) / 2;
    y = (screenheight - dlgheight) / 2;

    /* Reposition Window left, top (x,y) */
    SetWindowPos(hwndWindow, NULL, x, y, 0, 0, SWP_NOSIZE);

    return TRUE;
}