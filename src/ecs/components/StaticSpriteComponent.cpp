#include "ecs/components/StaticSpriteComponent.h"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	StaticSpriteComponent::StaticSpriteComponent(const char* path) {
		LoadSprite(path);
	}

	void StaticSpriteComponent::LoadSprite(const char* path) {
		m_Texture = g_ResourceManager->LoadTexture(path);
	}

	ComponentType StaticSpriteComponent::GetType() {
		return ComponentType::StaticSpriteType;
	}
}