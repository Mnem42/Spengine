#pragma once
#include <stdint.h>
#include <iostream>
#include <vector>

namespace spengine {
	namespace events {
		struct Evt {
			uint8_t listener = NULL;
			uint8_t evt_type = NULL;
			void* data = NULL;
			void* retdata = NULL;
			volatile bool is_valid = false;
			volatile bool return_ready = false;
		};

		typedef std::vector<Evt*> EvtQuene;
		typedef bool(EvtConsumer)(Evt*);
		typedef bool(EvtPrecheck)(Evt*);

		struct Evtquene_tracker {
			EvtQuene* system_quene;
			EvtQuene* system_cb_quene;
			EvtQuene* custom_evts;
		};
	}
	namespace evt_quene_utils {
		uint8_t consume_evt(spengine::events::EvtQuene* quene, spengine::events::EvtConsumer cb, void* retdata) {
			if (quene->front()->evt_type == NULL) {
				return 1;
			}
			uint8_t retval = cb(quene->front());

			if (retdata != NULL) {
				retdata = quene->front()->retdata;
			}

			quene->erase(quene->begin());
			return retval;
		}
		template<spengine::events::EvtPrecheck precheck> uint8_t quenestart_valid_check(spengine::events::EvtQuene* quene) {
			if (precheck(quene->front())) {
				return quene->front();
			}
			quene->erase(quene->begin());
		}
		template<spengine::events::EvtPrecheck precheck> uint8_t precheck_quene(spengine::events::EvtQuene* quene) {
			for (int i = 0; i < quene->size(); i++) {
				if (!precheck(quene->front())) {
					quene->erase(quene->begin());
				}
			}
		}
		template<typename Contained> void add_evt(spengine::events::EvtQuene* quene, uint8_t listener, uint8_t evt_type, Contained* item) {
			quene->push_back(new spengine::events::Evt{
				listener,
				evt_type,
				(void*)item,
				NULL,
				false,
				false
			});
			return;
		}
	}
}