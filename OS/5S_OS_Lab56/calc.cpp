#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <atlstr.h>
#include <Uxtheme.h>
#include "calcRes.h"

enum Operation
{
    PLUS,
    MINUS,
    DIVIDE,
    MULTIPLY,
    NOTHING
};

Operation lastOperaion = NOTHING;
TCHAR beforeNum[100];

LRESULT CALLBACK
DlgProc(HWND hDlg, UINT message, WPARAM wParam,
        LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    MSG msg;
    DialogBox(hInstance, (LPCTSTR)IDD_DLGTEST, NULL,
              (DLGPROC)DlgProc);
    RegisterHotKey(NULL, HK_PLUS, NULL, VK_F10);
    // RegisterHotKey(NULL, HK_MINUS, NULL, VK_OEM_MINUS);
    // RegisterHotKey(NULL, HK_MULTIPLY, NULL, '*');
    // RegisterHotKey(NULL, HK_DIVIDE, NULL, '/');
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
    long long a = 0;
    long long b = 0;
    long long c = 0;
    switch (message)
    {
    case WM_INITDIALOG:
        return TRUE;
    case WM_HOTKEY:
        MessageBox(NULL,
                   _T("Hotkey pressed"),
                   _T("Windows Desktop Guided Tour"),
                   NULL);
        // switch (HIWORD(lParam))
        // {
        // case VK_F10:
        //     GetDlgItemText(hDlg, IDC_NUM, beforeNum, 100);
        //     SetDlgItemText(hDlg, IDC_NUM, TEXT(""));
        //     lastOperaion = PLUS;
        //     return TRUE;
        // default:
        //     return TRUE;
        // }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_PLUS:
            GetDlgItemText(hDlg, IDC_NUM, beforeNum, 100);
            SetDlgItemText(hDlg, IDC_NUM, TEXT(""));
            lastOperaion = PLUS;
            return TRUE;
        case IDC_MINUS:
            GetDlgItemText(hDlg, IDC_NUM, beforeNum, 100);
            SetDlgItemText(hDlg, IDC_NUM, TEXT(""));
            lastOperaion = MINUS;
            return TRUE;
        case IDC_DIVIDE:
            GetDlgItemText(hDlg, IDC_NUM, beforeNum, 100);
            SetDlgItemText(hDlg, IDC_NUM, TEXT(""));
            lastOperaion = DIVIDE;
            return TRUE;
        case IDC_MULTIPLY:
            GetDlgItemText(hDlg, IDC_NUM, beforeNum, 100);
            SetDlgItemText(hDlg, IDC_NUM, TEXT(""));
            lastOperaion = MULTIPLY;
            return TRUE;
        case IDC_EQ:
            a = _tstoll(beforeNum);
            GetDlgItemText(hDlg, IDC_NUM, beforeNum, 100);
            b = _tstoll(beforeNum);
            switch (lastOperaion)
            {
            case PLUS:
                c = a + b;
                break;
            case MINUS:
                c = a - b;
                break;
            case DIVIDE:
                c = a / b;
                break;
            case MULTIPLY:
                c = a * b;
                break;
            default:
                break;
            }
            SetDlgItemText(hDlg, IDC_NUM, TEXT(""));
            _stprintf(beforeNum, TEXT("%lld"), c);
            SetDlgItemText(hDlg, IDC_NUM, beforeNum);
            return TRUE;
        case IDCANCEL:
            PostQuitMessage(0);
            return TRUE;
        }
        break;
    default:
        return FALSE;
    }

    return FALSE;
}