#include "ecs/components/CameraComponent.h"

namespace Aurora {
	CameraComponent::CameraComponent(TransformComponent& transform)
		: m_Transform(transform) {
	}

	ComponentType CameraComponent::GetType() {
		return ComponentType::CameraType;
	}

	void CameraComponent::Update() {
	}
}