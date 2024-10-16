#pragma once

namespace spengine {
	namespace specification {
		enum BuiltinHandlerMap {
			Capabilities_query = 0x01,
			Set_active_modules = 0x02,

			Drawer_required_A = 0x08,
			Drawer_required_B = 0x09,
			Drawer_optional_A = 0x0A,
			Drawer_optional_B = 0x0B,
		};
		enum DrawerEvtTypes {
			//required set A
			Draw_bitmap = 0x01,
			Draw_rect   = 0x02,
			Draw_tri    = 0x03,

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
		enum CapabilityQueryType {
			DrawDriver_Query,
			AudioDriver_Query,
			CPU_Query,
			API_Query
		};
	}
	namespace spec_drawer {
		struct TriPayload {
			math::coords::DisplayCoord c0;
			math::coords::DisplayCoord c1;
			math::coords::DisplayCoord c2;
		};
		struct RectPayload {
			math::coords::DisplayCoord x;
			math::coords::DisplayCoord y;
			math::coords::DisplayCoord w;
			math::coords::DisplayCoord h;
		};
		struct ColTriPayload {
			math::coords::DisplayCoord c0;
			math::coords::DisplayCoord c1;
			math::coords::DisplayCoord c2;
			math::colour::RGB24 colour;
		};
		struct ColRectPayload {
			math::coords::DisplayCoord x;
			math::coords::DisplayCoord y;
			math::coords::DisplayCoord w;
			math::coords::DisplayCoord h;
			math::colour::RGB24 colour;
		};
	}
	namespace spec_cababilityreq {
		struct CapabilityQueryRet {
			char* description;
			char* source;
			bool enabled     = false;
			bool query_valid = false;
			general_interface::Version version;
		};
	}
}