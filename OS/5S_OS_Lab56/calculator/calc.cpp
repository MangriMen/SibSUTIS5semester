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
    EQUAL
};

enum ClearState
{
    NOTHING,
    LAST,
    ALL
};

TCHAR beforeNum[100];
Operation lastOperation = EQUAL;
ClearState isClear = NOTHING;

LRESULT CALLBACK
DlgProc(HWND hDlg, UINT message, WPARAM wParam,
        LPARAM lParam);

void addNumberToTextEdit(HWND hDlg, int id, int num);
void shiftNumberToBuffer(HWND hDlg, int edittextMainId, int edittextBufferId, TCHAR *buffer);
void addActionToTextEdit(HWND hDlg, int id);
void rememberOperation(HWND hDlg, Operation newOperation, int edittextMainId, int edittextBufferId, TCHAR *buffer);
BOOL CenterWindowOnDesktop(HWND hwndWindow);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    DialogBox(hInstance, (LPCTSTR)IDD_DLGTEST, NULL,
              (DLGPROC)DlgProc);
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
        CenterWindowOnDesktop(hDlg);
        EnableWindow(GetDlgItem(hDlg, IDC_BEFORE_NUM), false);
        return TRUE;
    case WM_HOTKEY:
        MessageBox(hDlg, TEXT("Hello"), TEXT("Title"), 0);
        return TRUE;
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
            GetDlgItemText(hDlg, IDC_NUM, beforeNum, sizeof(beforeNum) / sizeof(beforeNum[0]));
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
                    lastOperation = EQUAL;
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
            lastOperation = EQUAL;
            isClear = ALL;
            return TRUE;
        case IDC_CLEAR:
            _stprintf(beforeNum, TEXT("%s"), TEXT(""));
            SetDlgItemText(hDlg, IDC_BEFORE_NUM, TEXT(""));
            SetDlgItemText(hDlg, IDC_NUM, TEXT(""));
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
        return TRUE;
    default:
        return FALSE;
    }

    return DefDlgProc(hDlg, message, wParam, lParam);
}

void addNumberToTextEdit(HWND hDlg, int id, int num)
{
    switch (isClear)
    {
    case LAST:
        SetDlgItemText(hDlg, IDC_NUM, TEXT(""));
        break;
    case ALL:
        _stprintf(beforeNum, TEXT("%s"), TEXT(""));
        SetDlgItemText(hDlg, IDC_BEFORE_NUM, TEXT(""));
        SetDlgItemText(hDlg, IDC_NUM, TEXT(""));
        break;
    default:
        break;
    }
    isClear = NOTHING;
    TCHAR tempBuf[100];
    GetDlgItemText(hDlg, id, tempBuf, sizeof(tempBuf) / sizeof(tempBuf[0]));
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
    GetDlgItemText(hDlg, edittextMainId, buffer, sizeof(buffer) / sizeof(buffer[0]));
    SetDlgItemText(hDlg, edittextBufferId, buffer);
    isClear = LAST;
}

void addActionToTextEdit(HWND hDlg, int id)
{
    HWND hWnd = GetDlgItem(hDlg, id);
    int textLength = GetWindowTextLength(hWnd) + 1;
    PTCHAR tempBuf = new TCHAR[textLength];
    GetDlgItemText(hDlg, id, tempBuf, textLength);
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
    isClear = NOTHING;
    if (lastOperation == EQUAL)
    {
        shiftNumberToBuffer(hDlg, edittextMainId, edittextBufferId, buffer);
    }
    else if (lastOperation == newOperation)
    {
        SendMessage(hDlg, WM_COMMAND, IDC_EQ, 0);
        isClear = LAST;
    }
    lastOperation = newOperation;
    addActionToTextEdit(hDlg, edittextBufferId);
}

BOOL CenterWindowOnDesktop(HWND hwndWindow)
{
    int screenwidth, screenheight;
    int dlgwidth, dlgheight, x, y;
    RECT rect;

    screenwidth = GetSystemMetrics(SM_CXSCREEN);
    screenheight = GetSystemMetrics(SM_CYSCREEN);

    GetWindowRect(hwndWindow, &rect);

    dlgwidth = rect.right - rect.left;
    dlgheight = rect.bottom - rect.top;

    x = (screenwidth - dlgwidth) / 2;
    y = (screenheight - dlgheight) / 2;

    SetWindowPos(hwndWindow, NULL, x, y, 0, 0, SWP_NOSIZE);

    return TRUE;
}