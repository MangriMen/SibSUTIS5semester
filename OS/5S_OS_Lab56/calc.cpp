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

Operation lastOperation = NOTHING;
TCHAR beforeNum[100];

LRESULT CALLBACK
DlgProc(HWND hDlg, UINT message, WPARAM wParam,
        LPARAM lParam);

void addNumberToTextEdit(HWND hDlg, int id, int num);
void shiftNumberToBuffer(HWND hDlg, int edittextMainId, int edittextBufferId, TCHAR *buffer);
void addActionToTextEdit(HWND hDlg, int id);
void rememberOperation(HWND hDlg, Operation newOperation, int edittextMainId, int edittextBufferId, TCHAR *buffer);

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
        //     lastOperation = PLUS;
        //     return TRUE;
        // default:
        //     return TRUE;
        // }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_PLUS:
            rememberOperation(hDlg, PLUS, IDC_NUM, IDC_BEFORE_NUM, beforeNum);
            return TRUE;
        case IDC_MINUS:
            rememberOperation(hDlg, MINUS, IDC_NUM, IDC_BEFORE_NUM, beforeNum);
            return TRUE;
        case IDC_DIVIDE:
            rememberOperation(hDlg, DIVIDE, IDC_NUM, IDC_BEFORE_NUM, beforeNum);
            return TRUE;
        case IDC_MULTIPLY:
            rememberOperation(hDlg, MULTIPLY, IDC_NUM, IDC_BEFORE_NUM, beforeNum);
            return TRUE;
        case IDC_EQ:
            a = _tstoll(beforeNum);
            GetDlgItemText(hDlg, IDC_NUM, beforeNum, 100);
            b = _tstoll(beforeNum);
            switch (lastOperation)
            {
            case PLUS:
                c = a + b;
                break;
            case MINUS:
                c = a - b;
                break;
            case DIVIDE:
                if (b == 0)
                {
                    _stprintf(beforeNum, TEXT("%s"), TEXT("Indefinite"));
                    SetDlgItemText(hDlg, IDC_NUM, beforeNum);
                    SetDlgItemText(hDlg, IDC_BEFORE_NUM, beforeNum);
                    lastOperation = NOTHING;
                    return TRUE;
                }
                c = a / b;
                break;
            case MULTIPLY:
                c = a * b;
                break;
            default:
                break;
            }
            _stprintf(beforeNum, TEXT("%lld"), c);
            SetDlgItemText(hDlg, IDC_NUM, beforeNum);
            SetDlgItemText(hDlg, IDC_BEFORE_NUM, beforeNum);
            lastOperation = NOTHING;
            return TRUE;
        case IDC_CLEAR:
            _stprintf(beforeNum, TEXT("%s"), TEXT(""));
            SetDlgItemText(hDlg, IDC_BEFORE_NUM, TEXT(""));
            SetDlgItemText(hDlg, IDC_NUM, TEXT(""));
            return TRUE;
        case IDC_CLEAR_LAST:
            SetDlgItemText(hDlg, IDC_NUM, TEXT(""));
            if (lastOperation == NOTHING)
            {
                _stprintf(beforeNum, TEXT("%s"), TEXT(""));
                SetDlgItemText(hDlg, IDC_BEFORE_NUM, TEXT(""));
            }
            return TRUE;
        case IDC_NULL:
            addNumberToTextEdit(hDlg, IDC_NUM, 0);
            return TRUE;
        case IDC_ONE:
            addNumberToTextEdit(hDlg, IDC_NUM, 1);
            return TRUE;
        case IDC_TWO:
            addNumberToTextEdit(hDlg, IDC_NUM, 2);
            return TRUE;
        case IDC_THREE:
            addNumberToTextEdit(hDlg, IDC_NUM, 3);
            return TRUE;
        case IDC_FOUR:
            addNumberToTextEdit(hDlg, IDC_NUM, 4);
            return TRUE;
        case IDC_FIVE:
            addNumberToTextEdit(hDlg, IDC_NUM, 5);
            return TRUE;
        case IDC_SIX:
            addNumberToTextEdit(hDlg, IDC_NUM, 6);
            return TRUE;
        case IDC_SEVEN:
            addNumberToTextEdit(hDlg, IDC_NUM, 7);
            return TRUE;
        case IDC_EIGHT:
            addNumberToTextEdit(hDlg, IDC_NUM, 8);
            return TRUE;
        case IDC_NINE:
            addNumberToTextEdit(hDlg, IDC_NUM, 9);
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

void addNumberToTextEdit(HWND hDlg, int id, int num)
{
    TCHAR tempBuf[100];
    GetDlgItemText(hDlg, id, tempBuf, sizeof(tempBuf) * sizeof(tempBuf[0]));
    int len = _tcslen(tempBuf);
    if (len >= 16)
    {
        return;
    }
    _stprintf(tempBuf + len, TEXT("%d"), num);
    SetDlgItemText(hDlg, id, tempBuf);
}

void shiftNumberToBuffer(HWND hDlg, int edittextMainId, int edittextBufferId, TCHAR *buffer)
{
    GetDlgItemText(hDlg, edittextMainId, buffer, sizeof(buffer) * sizeof(buffer[0]));
    SetDlgItemText(hDlg, edittextMainId, TEXT(""));
    SetDlgItemText(hDlg, edittextBufferId, buffer);
}

void addActionToTextEdit(HWND hDlg, int id)
{
    TCHAR tempBuf[100];
    GetDlgItemText(hDlg, id, tempBuf, sizeof(tempBuf) * sizeof(tempBuf[0]));
    int len = _tcslen(tempBuf);
    int pos = len;
    if (!_istdigit(tempBuf[len - 1]))
    {
        pos--;
    }
    TCHAR oper_[1];
    switch (lastOperation)
    {
    case PLUS:
        _stprintf(oper_, TEXT("%s"), TEXT("+"));
        break;
    case MINUS:
        _stprintf(oper_, TEXT("%s"), TEXT("-"));
        break;
    case DIVIDE:
        _stprintf(oper_, TEXT("%s"), TEXT("/"));
        break;
    case MULTIPLY:
        _stprintf(oper_, TEXT("%s"), TEXT("*"));
        break;
    default:
        break;
    }
    _stprintf(tempBuf + pos, TEXT("%s"), oper_);
    SetDlgItemText(hDlg, id, tempBuf);
}

void rememberOperation(HWND hDlg, Operation newOperation, int edittextMainId, int edittextBufferId, TCHAR *buffer)
{
    if (lastOperation == NOTHING)
    {
        shiftNumberToBuffer(hDlg, edittextMainId, edittextBufferId, buffer);
    }
    lastOperation = newOperation;
    addActionToTextEdit(hDlg, edittextBufferId);
}