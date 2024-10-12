#pragma once
#include "stdint.h"
#include "../core/math.h"

namespace spengine {
	//Follow this spec to make switching out drivers simpler and faster.
	//It also means you have to write slightly less code, as some functions
	//are implemented here.
	namespace Graphics_templates {
		namespace Event_types {
			enum EvtGroup {
				Outline,
				Shaded,
				Text,
				NoBackGround,
				ShadedPrimitives,
				Circles,
				UI
			};

			//These are required
			constexpr uint8_t evt_draw_outline_tri  = 0x01;
			constexpr uint8_t evt_draw_outline_rect = 0x02;
			constexpr uint8_t evt_draw_shaded_tri   = 0x10;
			constexpr uint8_t evt_draw_shaded_rect  = 0x11;
			constexpr uint8_t evt_draw_text         = 0x21;

			//These are optional (there is a seperate flag for if a group
			//is not defined for whatever reason). Circles are in their
			//own group, since they can be created in slightly higher level
			//software, but there are cases where it should really be separate
			//(e.g. relaying drawing instructions to another app)
			constexpr uint8_t evt_draw_transparent_outline_tri  = 0x30;
			constexpr uint8_t evt_draw_transparent_outline_rect = 0x31;
			constexpr uint8_t evt_draw_shaded_tri_alpha         = 0x40;
			constexpr uint8_t evt_draw_shaded_rect_alpha        = 0x41;

			constexpr uint8_t evt_draw_outline_circle             = 0x50;
			constexpr uint8_t evt_draw_shaded_circle              = 0x51;
			constexpr uint8_t evt_draw_shaded_circle_alpha        = 0x62;
			constexpr uint8_t evt_draw_transparent_outline_circle = 0x63;

			//These are optional
			constexpr uint8_t evt_draw_text_bgadded = 0x70;
			constexpr uint8_t evt_draw_text_bgadded = 0x71;
		}
		namespace Event_payloads {
			//Ignore this
			namespace __usings {
				using namespace spengine::math::coords;
			}
			struct Tripayload {
				__usings::DisplayCoord c0;
				__usings::DisplayCoord c1;
				__usings::DisplayCoord c2;
			};
		}
	}
}