#pragma once
#include "math.h"
#include "events.h"
#include "specification.h"

namespace spengine {
	namespace Environments {
		struct Environment {
			spengine::Events::Evtquene_tracker* evts;
			spengine::Events::UsedApiSet usedapis;
		};
	}
}