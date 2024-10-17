#pragma once
#include "math.h"
#include "events.h"
#include "interface.h"
#include "specification.h"

namespace spengine {
	namespace Environments {
		struct Environment {
			spengine::events::Evtquene_tracker* evts;
		};
	}
}