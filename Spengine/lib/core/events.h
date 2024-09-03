#pragma once
#include <stdint.h>
#include <iostream>
#include <vector>

namespace spengine {
	namespace Events {
		struct Evt {
			uint16_t      evt_type = NULL;
			void* data = NULL;
			void* retdata = NULL;
			volatile bool return_ready = false;
		};

		typedef std::vector<Evt*> EvtQuene;
		typedef uint8_t(EvtConsumer)(Evt*);
		typedef uint8_t(EvtPrecheck)(Evt*);

		typedef uint16_t UsedApiSet;
		namespace UsedApiMasks {
			constexpr uint16_t graphics_used = 0x0001;
			constexpr uint16_t audio_used = 0x0002;
			constexpr uint16_t physics_used = 0x0004;
		}

		struct Evtquene_tracker {
			EvtQuene* drawer_evts;
			EvtQuene* audio_evts;
			EvtQuene* physics_evts;
			EvtQuene* custom_evts;
		};

		namespace Events {
			uint8_t consume_evt(EvtQuene* quene, EvtConsumer cb) {
				if (quene->front()->evt_type == NULL) {
					return 1;
				}
				uint8_t retval = cb(quene->front());
				quene->erase(quene->begin());
				return retval;
			}
			uint8_t consume_evt_with_precheck(EvtQuene* quene, EvtConsumer consumer, EvtPrecheck precheck) {
				if (precheck(quene->front())) {
					return consumer(quene->front());
				}
				quene->erase(quene->begin());
			}

			template<typename Contained> void add_evt(EvtQuene* quene, uint16_t evt_type, Contained* item) {
				quene->push_back(new Evt{
					evt_type,
					(void*)item,
					NULL,
					false
					});
				return;
			}
		}
	}
}