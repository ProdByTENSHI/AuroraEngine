#pragma once

#include <vector>

#include "ecs/ECS_Definitions.h"
#include "globals/AuroraTypes.hpp"
#include "tenshiUtil/eventsystem/EventSystem.h"

namespace Aurora
{
	struct System
	{
		System(Signature signature, u8 id);
		virtual ~System() {}

		// Only holds Entities that have the Signature of the System
		std::vector<Entity> m_Entities;

		// Component Signature of the System
		const Signature m_Signature;

		// Unique System ID
		const u8 m_Id;
	};
}