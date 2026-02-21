#include "ecs/components/SpriteComponent.h"

namespace Aurora {
	SpriteComponent::SpriteComponent(Texture* texture)
		: m_Texture(texture) {
	}

	ComponentType SpriteComponent::GetType() { return ComponentType::SpriteType; }
} // namespace Aurora