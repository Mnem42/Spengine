#pragma once
#include <exception>
#include "../../core/events.h"
#include "../../core/specification.h"
#include <Windows.h>
#include <string>

namespace spengine_winapi {

	bool capability_query_handler(spengine::events::Evt* evt) {
		using namespace spengine::specification;
		using namespace spengine::spec_cababilityreq;

		std::string description = "WINAPI wrapper for spengine";
		std::string source      = "spengine devs";

		switch (static_cast<CapabilityQueryType>(evt->evt_type)) {
		case API_Query: {
			auto tmp = static_cast<CapabilityQueryRet*>(evt->retdata);
			tmp->description = new char[](description.c_str());
			tmp->source      = new const_cast<char*>(source.c_str());

			tmp->enabled     = TRUE;
			tmp->version = { 
				spengine_winapi::wrapper_ver::major,
				spengine_winapi::wrapper_ver::minor,
				spengine_winapi::wrapper_ver::patch,
				0
			};

			evt->return_ready = true;
			return false;
		}
		default:
			return true;
		}
	}
}