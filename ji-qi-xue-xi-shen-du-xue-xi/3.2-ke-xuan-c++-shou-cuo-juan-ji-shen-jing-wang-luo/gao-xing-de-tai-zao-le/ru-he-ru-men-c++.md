---
description: 其实很简单
---

# 如何入门C++

## 清晰的C++教程 点击前往->[Runoob](https://www.runoob.com/cplusplus/cpp-tutorial.html)

## 1. C++基本程序模板：

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello World!" << endl;
    return 0;
}
```

## 2. C++ 最简单的窗口程序模板(使用Win32 API)：

```cpp
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    // 注册窗口类
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"BasicWindow";
    RegisterClass(&wc);

    // 创建窗口
    HWND hwnd = CreateWindowEx(
        0,
        L"BasicWindow",
        L"我的窗口",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);

    // 消息循环
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
```

第一个模板是最基本的C++控制台程序模板，包含了必要的头文件和main函数。

第二个模板是最简单的Windows窗口程序，使用Win32 API创建一个基本窗口。这个模板会创建一个800x600像素的标准窗口，包含最小化、最大化和关闭按钮。
