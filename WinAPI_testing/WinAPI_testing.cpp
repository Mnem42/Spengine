#ifndef UNICODE
#define UNICODE
#endif 
//#undef WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "../Spengine/lib/core/environment.h"
#include "../Spengine/lib/templates/Windows/winapi.h"
#include "gdiplus.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

spengine_winapi::WindowManager* manager;
spengine::events::EvtQuene* quene;

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Spengine testing",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    quene = new spengine::events::EvtQuene();
    manager = new spengine_winapi::WindowManager(true);

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nShowCmd);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        //Clear screen
        quene->push_back(new spengine::events::Evt{
            spengine::specification::Drawer_required_A,
            spengine::specification::Clear_screen,
            NULL,
            NULL
        });

        //Draw
        quene->push_back(new spengine::events::Evt{
            spengine::specification::Drawer_required_A,
            spengine::specification::Draw_rect,
            new spengine::spec_drawer::RectPayload{
                5,5,55,55
            },
            NULL
        });
        quene->push_back(new spengine::events::Evt{
            spengine::specification::Drawer_required_A,
            spengine::specification::Draw_rect,
            new spengine::spec_drawer::RectPayload{
                35,35,85,85
            },
            NULL
        });

        quene->push_back(new spengine::events::Evt{
            spengine::specification::Drawer_required_A,
            spengine::specification::Draw_tri,
            new spengine::spec_drawer::TriPayload{
                35,45,
                70,5,
                70,45
            },
            NULL
        });

        for (int i = 0; i < quene->size(); i++) {
            if (manager->consume_drawing_event(hdc, ps, quene->at(i))) {
                quene->erase(quene->begin());
                i--;
            }
        }

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}