#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

#pragma comment(linker, "/SUBSYSTEM:WINDOWS")

class Point {
protected:
    int X, Y, Cvet;
public:
    Point(int XN, int YN, int Color) : X(XN), Y(YN), Cvet(Color) {}
    virtual ~Point() {}
    virtual void Show(HDC hdc) = 0;
    virtual void Hide(HDC hdc) = 0;
    void Locat(int& XL, int& YL) const { XL = X; YL = Y; }
    virtual void Fly(HWND hwnd, int Cost);
};

void Point::Fly(HWND hwnd, int Cost) {
    HDC hdc = GetDC(hwnd);
    Show(hdc);
    ReleaseDC(hwnd, hdc);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    bool running = true;
    while (running) {
        // Обрабатываем сообщения окна, чтобы оно не зависало
        MSG msg;
        while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_KEYDOWN) {
                running = false; // нажата клавиша – выходим
            }
        }

        if (!running) break;

        int XX, YY;
        Locat(XX, YY);

        RECT rect;
        GetClientRect(hwnd, &rect);
        int maxX = rect.right;
        int maxY = rect.bottom;

        do {
            double r = (std::rand() / (double)RAND_MAX) - 0.5;
            XX += static_cast<int>(std::round(r * Cost));
        } while (XX <= 0 || XX >= maxX);

        do {
            double r = (std::rand() / (double)RAND_MAX) - 0.5;
            YY += static_cast<int>(std::round(r * Cost));
        } while (YY <= 0 || YY >= maxY);

        hdc = GetDC(hwnd);
        Hide(hdc);
        X = XX; Y = YY;
        Show(hdc);
        ReleaseDC(hwnd, hdc);

        // Принудительная перерисовка окна
        InvalidateRect(hwnd, NULL, FALSE);
        UpdateWindow(hwnd);

        Sleep(300);
    }
}

class Krug : public Point {
protected:
    int Radius;
public:
    Krug(int XN, int YN, int R, int Color) : Point(XN, YN, Color), Radius(R) {}
    void Show(HDC hdc) override {
        HBRUSH brush = CreateSolidBrush(RGB(Cvet, Cvet, Cvet));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
        Ellipse(hdc, X - Radius, Y - Radius, X + Radius, Y + Radius);
        SelectObject(hdc, oldBrush);
        DeleteObject(brush);
    }
    void Hide(HDC hdc) override {
        HBRUSH brush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
        Ellipse(hdc, X - Radius, Y - Radius, X + Radius, Y + Radius);
        SelectObject(hdc, oldBrush);
        DeleteObject(brush);
    }
};

class Ring : public Krug {
    int Width;
public:
    Ring() : Krug(0, 0, 0, 0), Width(0) {}
    Ring(int XN, int YN, int R, int Color, int Wid) : Krug(XN, YN, R, Color), Width(Wid) {}
    void Show(HDC hdc) override {
        Krug::Show(hdc);
        HBRUSH brush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
        Ellipse(hdc, X - (Radius - Width), Y - (Radius - Width),
            X + (Radius - Width), Y + (Radius - Width));
        SelectObject(hdc, oldBrush);
        DeleteObject(brush);
    }
};

Krug* g_testKrug = nullptr;
Ring* g_testRing = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        g_testKrug = new Krug(150, 40, 50, 100);
        g_testRing = new Ring(450, 80, 90, 150, 30);
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        if (g_testKrug) g_testKrug->Show(hdc);
        if (g_testRing) g_testRing->Show(hdc);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_KEYDOWN:
        if (g_testKrug && g_testRing) {
            g_testKrug->Fly(hwnd, 100);
            g_testRing->Fly(hwnd, 60);
            g_testKrug->Fly(hwnd, 60);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    case WM_DESTROY:
        delete g_testKrug;
        delete g_testRing;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Lab7WindowClass";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    if (!RegisterClass(&wc)) return 0;

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Лабораторная работа 7",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, hInstance, nullptr);
    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}