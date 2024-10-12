#pragma once
#include "events.h"

namespace spengine {
	namespace Environments {
		struct Environment {
			spengine::Events::Evtquene_tracker* evts;
			spengine::Events::UsedApiSet usedapis;
		};
	}
}