#pragma once

#include <glm/glm.hpp>

#include "ecs/components/TransformComponent.h"
#include "globals/AuroraTypes.hpp"
#include "tenshiUtil/eventsystem/EventSystem.h"
#

namespace Aurora {
	class CameraComponent : public virtual Component {
	public:
		CameraComponent(TransformComponent& transform);
		~CameraComponent();

		ComponentType GetType() override;

		void Update();

	private:
		mutable const TransformComponent& m_Transform;
	};
}