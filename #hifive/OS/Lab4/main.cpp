#include <iostream>
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASS wc;
    LPCSTR lpszAppName = "CTemplate1";
    BOOL ret;
    //И Н И Ц И А Л И З А Ц И Я К Л А С С А О К Н А
    wc.lpszClassName = lpszAppName;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = (WNDPROC)MyWndProc;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = 0;
    wc.lpszMenuName = 0;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    if (!RegisterClass(&wc))
    {
        return 0;
    }
    hWnd = CreateWindow(lpszAppName,
                        lpszAppName,
                        WS_OVERLAPPEDWINDOW,
                        100,
                        100,
                        400,
                        200,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);
    ret = RegisterHotKey(hWnd, 0xB001, MOD_CONTROL | MOD_ALT, 'W');
    ShowWindow(hWnd, SW_HIDE);
    UpdateWindow(hWnd);
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
