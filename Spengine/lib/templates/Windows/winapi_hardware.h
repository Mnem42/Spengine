#pragma once
#include <exception>
#include "../../core/events.h"
#include "../../core/specification.h"
#include <Windows.h>

namespace spengine_winapi {

	bool capability_query_handler(spengine::events::Evt* evt) {
		using namespace spengine::specification;
		using namespace spengine::spec_cababilityreq;

		CapabilityQueryRet tmp;
		switch (static_cast<CapabilityQueryType>(evt->evt_type)) {
		case API_Query: {
			OSVERSIONINFOEX ver;

			VerifyVersionInfo(&ver, VER_BUILDNUMBER | VER_MAJORVERSION | VER_MINORVERSION, NULL);

			DWORD build = ver.dwBuildNumber;
			DWORD minorver = ver.dwMinorVersion;
			DWORD majorver = ver.dwMajorVersion;

			tmp.id      = "WINAPI";
			tmp.source  = "";
			tmp.enabled = TRUE;
			tmp.version = { majorver,minorver,build };

			evt->retdata      = (void*)(&tmp);
			evt->return_ready = true;
			return false;
		}
		default:
			return true;
		}
	}
}