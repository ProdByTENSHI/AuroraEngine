#pragma once

#include "ecs/ComponentTypes.h"
#include "globals/AuroraTypes.hpp"

namespace Aurora {
	// Base Class for all ECS Components
	struct Component {
		virtual ~Component() {}

		// Returns the Component Type
		virtual ComponentType GetType() = 0;
	};
} // namespace tenshi
