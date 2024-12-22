#pragma once
#include "math.h"
#include "interface.h"

namespace spengine {
	namespace specification {
		enum BuiltinHandlerMap {
			Capabilities_query = 0x01,
			Set_active_modules = 0x02,

			Drawer_required_A = 0x08,
			Drawer_required_B = 0x09,
			Drawer_optional_A = 0x0A,
			Drawer_optional_B = 0x0B,

			Window_management = 0x10,
			Window_callbacks  = 0x11
		};
		enum DrawerEvtTypes {
			//required set A
			Clear_screen = 0x01,
			Draw_bitmap  = 0x02,
			Draw_rect    = 0x03,
			Draw_tri     = 0x04,

			//required set B
			Draw_shaded_rect = 0x08,
			Draw_shaded_tri  = 0x09,
			
			//optional set A
			Draw_circle        = 0x0A,
			Draw_shaded_circle = 0x0B,

			//optional set B
			Draw_text = 0x0A,

			//optional set C
			Invert_colour_area = 0x0B
		};
		enum WindowEvtTypes {
			Window_create  = 0x01,
			Window_destroy = 0x02,
			Window_draw    = 0x03
		};
		enum CapabilityQueryType {
			DrawDriver_Query,
			AudioDriver_Query,
			CPU_Query,
			API_Query
		};
	}
	namespace spec_drawer {
		struct TriPayload {
			uint16_t x1;
			uint16_t y1;
			uint16_t x2;
			uint16_t y2;
			uint16_t x3;
			uint16_t y3;
		};
		struct RectPayload {
			uint16_t x1;
			uint16_t y1;
			uint16_t x2;
			uint16_t y2;
		};
		struct ColTriPayload {
			uint16_t x1;
			uint16_t x2;
			uint16_t x3;
			uint16_t y1;
			uint16_t y2;
			uint16_t y3;
			spengine::math::colour::RGB24 colour;
		};
		struct ColRectPayload {
			uint16_t x1;
			uint16_t y1;
			uint16_t x2;
			uint16_t y2;
			spengine::math::colour::RGB24 colour;
		};
	}
	namespace spec_cababilityreq {
		struct CapabilityQueryRet {
			char* description = NULL;
			char* source      = NULL;
			bool enabled      = false;
			general_interface::Version version;
		};
	}
	namespace spec_windowing {
		struct WindowQueryInput_WINAPI {
			LPCWSTR name;
			HINSTANCE hinst;
			HINSTANCE hprevinst;
			PWSTR pcmdline;
			int ncmdshow;
		};
	}
}