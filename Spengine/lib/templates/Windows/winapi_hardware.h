#pragma once
#include <exception>
#include "../../core/events.h"
#include "../../core/specification.h"
#include <string>

namespace spengine_winapi {

	bool capability_query_handler(spengine::events::Evt* evt) {
		using namespace spengine::specification;
		using namespace spengine::spec_cababilityreq;

		std::string description = "WINAPI wrapper for spengine";
		std::string source      = "spengine devs";

		switch (static_cast<CapabilityQueryType>(evt->evt_type)) {
		case API_Query: {
			auto tmp = new CapabilityQueryRet;
			tmp->description = const_cast<char*>(description.c_str());
			tmp->source      = const_cast<char*>(source.c_str());

			tmp->enabled     = TRUE;
			tmp->version = { 
				spengine_winapi::wrapper_ver::major,
				spengine_winapi::wrapper_ver::minor,
				spengine_winapi::wrapper_ver::patch,
				0
			};

			evt->retdata = static_cast<void*>(tmp);
			evt->return_ready = true;
			return false;
		}
		default:
			return true;
		}
	}
}