#include "ecs/components/StaticSpriteComponent.h"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	StaticSpriteComponent::StaticSpriteComponent(const char* path) {
		LoadSprite(path);
	}

	void StaticSpriteComponent::LoadSprite(const char* path) {
		m_Texture = g_ResourceManager->LoadTexture(path);
	}

	void StaticSpriteComponent::SetSpriteSheetData(u32 col, u32 row, u32 colNum, u32 rowNum)
	{
	}

	ComponentType StaticSpriteComponent::GetType() {
		return ComponentType::StaticSpriteType;
	}
}