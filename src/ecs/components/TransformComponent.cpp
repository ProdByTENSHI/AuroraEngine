#include "ecs/components/TransformComponent.h"

#include <iostream>

namespace Aurora {
	TransformComponent::TransformComponent() { Scale(1.0f); }

	TransformComponent::TransformComponent(const glm::vec2& pos,
		const glm::vec2& rot,
		const glm::vec2& scale) {
		Scale(scale);
		Rotate(glm::vec2(1.0f, 0.0f), rot.x);
		Rotate(glm::vec2(0.0f, 1.0f), rot.y);
		Translate(pos);
	}

	ComponentType TransformComponent::GetType() {
		return ComponentType::TransformType;
	}
} // namespace tenshi