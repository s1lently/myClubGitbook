// PerceptronViz.cpp
#include <windows.h>
#include <vector>
#include <cmath>
#include <string>

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Point structure
struct Point {
    float x, y;
    bool type; // true for blue, false for yellow
};

// Global variables
std::vector<Point> points;
float weights[3] = { 0, 0, 0 }; // w1, w2, bias
float learningRate = 0.1f;
bool isTraining = false;
HWND hwndMain, hwndLREdit, hwndDelayEdit, hwndStatus;
HBRUSH hBlueBrush, hYellowBrush;

// Function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawPoint(HDC hdc, Point p);
void DrawLine(HDC hdc);
void TrainPerceptron();
float Predict(float x, float y);

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register window class
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"PerceptronViz";
    RegisterClassEx(&wc);

    // Create brushes
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
    hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));

    // Create main window
    hwndMain = CreateWindow(
        L"PerceptronViz", L"Perceptron Visualization",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, hInstance, NULL
    );

    // Create controls
    CreateWindow(L"BUTTON", L"Blue Point", WS_CHILD | WS_VISIBLE,
        10, 10, 100, 30, hwndMain, (HMENU)1, hInstance, NULL);

    CreateWindow(L"BUTTON", L"Yellow Point", WS_CHILD | WS_VISIBLE,
        120, 10, 100, 30, hwndMain, (HMENU)2, hInstance, NULL);

    CreateWindow(L"BUTTON", L"Clear All", WS_CHILD | WS_VISIBLE,
        230, 10, 100, 30, hwndMain, (HMENU)3, hInstance, NULL);

    // Learning Rate controls
    CreateWindow(L"STATIC", L"Learning Rate:", WS_CHILD | WS_VISIBLE,
        10, 50, 100, 20, hwndMain, NULL, hInstance, NULL);

    hwndLREdit = CreateWindow(L"EDIT", L"0.1", WS_CHILD | WS_VISIBLE | WS_BORDER,
        120, 50, 50, 20, hwndMain, NULL, hInstance, NULL);

    // Delay Time controls
    CreateWindow(L"STATIC", L"Delay (ms):", WS_CHILD | WS_VISIBLE,
        190, 50, 80, 20, hwndMain, NULL, hInstance, NULL);

    hwndDelayEdit = CreateWindow(L"EDIT", L"100", WS_CHILD | WS_VISIBLE | WS_BORDER,
        280, 50, 50, 20, hwndMain, NULL, hInstance, NULL);

    CreateWindow(L"BUTTON", L"Train All Points", WS_CHILD | WS_VISIBLE,
        10, 80, 100, 30, hwndMain, (HMENU)4, hInstance, NULL);

    hwndStatus = CreateWindow(L"STATIC", L"Click canvas to add points, then click Train to start",
        WS_CHILD | WS_VISIBLE,
        10, 120, 300, 20, hwndMain, NULL, hInstance, NULL);

    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Cleanup
    DeleteObject(hBlueBrush);
    DeleteObject(hYellowBrush);
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static bool addBluePoint = true;

    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Draw canvas background
        RECT canvasRect = { 0, 150, WINDOW_WIDTH, WINDOW_HEIGHT };
        FillRect(hdc, &canvasRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

        // Draw decision boundary
        DrawLine(hdc);

        // Draw points
        for (const auto& point : points) {
            DrawPoint(hdc, point);
        }

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_LBUTTONDOWN: {
        if (HIWORD(lParam) > 150) { // Only handle clicks in canvas area
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);

            // Normalize coordinates to [-1, 1]
            float normX = (float)(x - WINDOW_WIDTH / 2) / (WINDOW_WIDTH / 2);
            float normY = -(float)(y - WINDOW_HEIGHT / 2) / (WINDOW_HEIGHT / 2);

            points.push_back({ normX, normY, addBluePoint });
            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;
    }

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case 1: // Blue Point button
            addBluePoint = true;
            break;

        case 2: // Yellow Point button
            addBluePoint = false;
            break;

        case 3: // Clear All button
            points.clear();
            weights[0] = weights[1] = weights[2] = 0;
            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case 4: // Train All Points button
            if (!isTraining) {
                isTraining = true;
                CreateThread(NULL, 0,
                    [](LPVOID param) -> DWORD {
                        TrainPerceptron();
                        isTraining = false;
                        return 0;
                    },
                    NULL, 0, NULL);
            }
            break;
        }
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void DrawPoint(HDC hdc, Point p) {
    // Convert normalized coordinates back to screen coordinates
    int screenX = (int)((p.x * WINDOW_WIDTH / 2) + WINDOW_WIDTH / 2);
    int screenY = (int)(-(p.y * WINDOW_HEIGHT / 2) + WINDOW_HEIGHT / 2);

    RECT pointRect = { screenX - 5, screenY - 5, screenX + 5, screenY + 5 };
    FillRect(hdc, &pointRect, p.type ? hBlueBrush : hYellowBrush);
}

void DrawLine(HDC hdc) {
    if (fabs(weights[1]) < 1e-6) return; // Avoid division by zero

    // Calculate two points for the line y = -(w1*x + w0)/w2
    float x1 = -1;
    float y1 = -(weights[0] * x1 + weights[2]) / weights[1];
    float x2 = 1;
    float y2 = -(weights[0] * x2 + weights[2]) / weights[1];

    // Convert to screen coordinates
    int screenX1 = (int)((x1 * WINDOW_WIDTH / 2) + WINDOW_WIDTH / 2);
    int screenY1 = (int)(-(y1 * WINDOW_HEIGHT / 2) + WINDOW_HEIGHT / 2);
    int screenX2 = (int)((x2 * WINDOW_WIDTH / 2) + WINDOW_WIDTH / 2);
    int screenY2 = (int)(-(y2 * WINDOW_HEIGHT / 2) + WINDOW_HEIGHT / 2);

    MoveToEx(hdc, screenX1, screenY1, NULL);
    LineTo(hdc, screenX2, screenY2);
}

float Predict(float x, float y) {
    return weights[0] * x + weights[1] * y + weights[2];
}

void TrainPerceptron() {
    const int MAX_EPOCHS = 1000;
    int epoch = 0;
    bool hasError;

    // Get learning rate from edit control
    wchar_t lrText[32];
    GetWindowText(hwndLREdit, lrText, 32);
    learningRate = _wtof(lrText);

    // Get delay time from edit control
    wchar_t delayText[32];
    GetWindowText(hwndDelayEdit, delayText, 32);
    int delayTime = _wtoi(delayText);
    // Ensure delay time is within reasonable bounds (1-5000ms)
    delayTime = max(1, min(5000, delayTime));

    do {
        hasError = false;
        for (const auto& point : points) {
            float prediction = Predict(point.x, point.y);
            float target = point.type ? 1.0f : -1.0f;

            if (prediction * target <= 0) { // Misclassification
                // Update weights
                weights[0] += learningRate * target * point.x;
                weights[1] += learningRate * target * point.y;
                weights[2] += learningRate * target;
                hasError = true;

                // 强制重绘以显示更新
                InvalidateRect(hwndMain, NULL, TRUE);
                UpdateWindow(hwndMain);

                // 使用用户设定的延迟时间
                Sleep(delayTime);
            }
        }

        // Update status
        wchar_t status[64];
        swprintf(status, 64, L"Training... Epoch %d", epoch);
        SetWindowText(hwndStatus, status);

        epoch++;
    } while (hasError && epoch < MAX_EPOCHS);

    // Update final status
    SetWindowText(hwndStatus, epoch < MAX_EPOCHS ? L"Training complete!" : L"Max epochs reached");
}