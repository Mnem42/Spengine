#pragma once

namespace spengine_winapi {

    class WindowManager {
    private: 
        spengine::events::EvtQuene* _quene = NULL; // This has to be public for win32 reasons
    public:
        
        WindowManager(spengine::events::EvtQuene* quene) {
            _quene = quene;
        }

        void consume_event(spengine::events::Evt* evt) {
            switch (evt->listener) {
            case spengine::specification::Window_create:
                generate_desktop_window_blank(evt);
            }
        }

        static LRESULT CALLBACK general_cb(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            WindowManager* _this;

            switch (uMsg)
            {
            case WM_NCCREATE:
                _this = static_cast<WindowManager*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

                SetLastError(0);
                if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(_this)))
                {
                    if (GetLastError() != 0)
                        return FALSE;
                }
            case WM_DESTROY:
                _this = reinterpret_cast<WindowManager*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
                if (_this) {
                    spengine::evt_quene_utils::add_evt(
                        _this->_quene,
                        spengine::specification::Window_callbacks,
                        spengine::specification::Window_destroy,
                        (void*)NULL
                    );
                }
                PostQuitMessage(0);
                return 0;

            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                // All painting occurs here, between BeginPaint and EndPaint.

                FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

                EndPaint(hwnd, &ps);
            }
            return 0;

            }
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        bool generate_desktop_window_blank(spengine::events::Evt* evt) {
            const wchar_t CLASS_NAME[] = L"Sample Window Class";

            WNDCLASS wc = { };
            auto data = static_cast<spengine::spec_windowing::WindowQueryInput_WINAPI*>(evt->data);

            wc.lpfnWndProc = general_cb;
            wc.hInstance = data->hinst;
            wc.lpszClassName = CLASS_NAME;

            RegisterClass(&wc);

            // Create the window.

            HWND hwnd = CreateWindowEx(
                0,                              // Optional window styles.
                CLASS_NAME,                     // Window class
                data->name,
                WS_OVERLAPPEDWINDOW,            // Window style

                // Size and position
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

                NULL,       // Parent window    
                NULL,       // Menu
                data->hinst,  // Instance handle
                NULL        // Additional application data
            );

            if (hwnd == NULL)
            {
                return 0;
            }

            ShowWindow(hwnd, data->ncmdshow);

            // Run the message loop.

            MSG msg = { };
            while (GetMessage(&msg, NULL, 0, 0) > 0)
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
}