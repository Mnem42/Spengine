#pragma once
#include <Windows.h>
#include "../../core/events.h"
#include "../../core/specification.h"

namespace spengine_winapi {
	bool hardware_query(spengine::specification::CapabilityQueryType query_type,HWND hwnd) {
		using namespace spengine::specification;
		using namespace spengine::spec_cababilityreq;

		CapabilityQueryRet tmp;
		switch (query_type) {
		case API_Query:
            DWORD dwVersion = 0;
            DWORD major_ver = 0;
            DWORD minor_ver = 0;
            DWORD build_num = 0;

            dwVersion = GetVersion();

            major_ver = (DWORD)(LOBYTE(LOWORD(dwVersion)));
            minor_ver = (DWORD)(HIBYTE(LOWORD(dwVersion)));

			if (dwVersion < 0x80000000)
				build_num = (DWORD)(HIWORD(dwVersion));

			tmp.id      = "WINAPI";
			tmp.source  = "";
			tmp.enabled = TRUE;
			tmp.version = { major_ver,minor_ver,build_num };

			return false;
		default:
			return true;
		}
	}
}