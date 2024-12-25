#pragma once
#define USE_GDIP
#ifdef USE_GDIP
#include "gdiplus.h"
#endif

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
                    draw_rect(hdc, data->x1, data->y1, data->x2, data->y2);
                    return true;
                }
                case spengine::specification::Draw_tri: {
                    auto data = (spengine::spec_drawer::TriPayload*)evt->data;
                    draw_tri(
                        hdc, {0,0,0},
                        data->x1, data->y1, 
                        data->x2, data->y2, 
                        data->x3, data->y3
                    );
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

        #ifndef USE_GDIP
        void draw_tri(HDC hdc, spengine::math::colour::RGB24 colour, int x, int y, int x2, int y2, int x3, int y3) {
            POINT points[3] = { {x,y},{x2,y2},{x3,y3} };
            Polygon(hdc, points, 3);
        }

        void draw_rect(HDC hdc,int x,int y, int x2, int y2) {
            Rectangle(hdc, x, y, x2, y2);
        }
        #else
        void draw_rect(HDC hdc, int x, int y, int x2, int y2) {
            using namespace Gdiplus;
            Pen pen(Color(255, 0, 0, 0), 1);
            Graphics g(hdc);

            g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
            g.DrawRectangle(&pen, x, y, x2 - x, y2 - y);
        }

        void draw_tri(HDC hdc, spengine::math::colour::RGB24 colour, int x, int y, int x2, int y2, int x3, int y3) {
            using namespace Gdiplus;
            Pen pen(Color(255, 0, 0, 0), 1);

            Point p0 = { x,y };
            Point p1 = { x2,y2 };
            Point p2 = { x3,y3 };
            Point arr[] = { p0,p1,p2 };
            Graphics g(hdc);

            g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
            g.DrawPolygon(&pen, arr, 3);
        }
        #endif

        void GDI_clear_screen(HDC hdc, PAINTSTRUCT& ps) {
            using namespace Gdiplus;
            Graphics g(hdc);

            g.Clear(Color(255, 255, 255));
        }
    };
}