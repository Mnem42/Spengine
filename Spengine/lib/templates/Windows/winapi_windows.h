#pragma once

namespace spengine_winapi {

    class WindowManager {
    private: 
        bool _GDI_initialised = false;
    public:
        
        WindowManager(bool GDI_initialised = false) {
            _GDI_initialised = GDI_initialised;
        }

        bool consume_drawing_event(HDC hdc, PAINTSTRUCT& ps, spengine::events::Evt* evt) {
            if (evt->listener == spengine::specification::Drawer_required_A) {
                switch (evt->evt_type) {
                case spengine::specification::Draw_rect: {
                    auto data = (spengine::spec_drawer::RectPayload*)evt->data;
                    GDI_draw_rect(hdc, data->x1, data->y1, data->x2, data->y2);
                    return true;
                }
                case spengine::specification::Clear_screen:
                    GDI_clear_screen(hdc,ps);
                    return true;
                default:
                    return false;
                }
            }
        }

        void GDI_draw_rect(HDC hdc,int x,int y, int x2, int y2) {
            Rectangle(hdc, x, y, x2, y2);
        }

        void GDI_clear_screen(HDC hdc, PAINTSTRUCT& ps) {
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        }
    };
}