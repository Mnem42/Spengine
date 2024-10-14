#pragma once
#include <exception>
#include "../../core/events.h"
#include "../../core/specification.h"
#include <Windows.h>

namespace spengine_winapi {

	bool capability_query(spengine::specification::CapabilityQueryType query_type,HWND hwnd) {
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

	class capability_evthandler{
	private:
		HWND hwnd=NULL;
	public:
		capability_evthandler(HWND hWnd) {
			hwnd = hWnd;
		}
		bool operator () (spengine::events::Evt* evt){
			if (hwnd != NULL) {
				evt->retdata=(void*)capability_query(static_cast<spengine::specification::CapabilityQueryType>(evt->evt_type), hwnd);
				return false;
			}
			else {
				throw new std::invalid_argument("Query invalid");
				return true;
			}
		}
	};
}