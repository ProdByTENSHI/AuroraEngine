#pragma once

#include "ecs/Component.h"

#include <SDL.h>
#include <memory>
#include <string>

namespace Aurora {
	class StaticSpriteComponent : public virtual Component {
	public:
		explicit StaticSpriteComponent(const char* path);

		void LoadSprite(const char* path);

		ComponentType GetType() override;

	public:
		SDL_Texture* m_Texture;
	};
}