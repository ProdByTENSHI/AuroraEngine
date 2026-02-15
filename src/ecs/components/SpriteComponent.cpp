#include "ecs/components/SpriteComponent.h"

namespace Aurora {
	SpriteComponent::SpriteComponent(std::shared_ptr<Texture> texture)
		: m_Texture(texture) {
	}

	ComponentType SpriteComponent::GetType() { return ComponentType::SpriteType; }
} // namespace Aurora