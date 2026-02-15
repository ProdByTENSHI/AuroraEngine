#pragma once

#include "ecs/Component.h"

#include <string>

namespace Aurora {
	class EntityNameComponent : public virtual Component {
	public:
		explicit EntityNameComponent(const std::string& name);

		ComponentType GetType() override;

	public:
		std::string m_Name = "Unnamed Entity";
	};
} // namespace Aurora
