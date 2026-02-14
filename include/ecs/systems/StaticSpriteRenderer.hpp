#pragma once

#include "ecs/System.h"

#include <SDL.h>
#include <vector>

namespace Aurora {
	typedef struct StaticSpriteBatch {
	public:

		SDL_Texture* m_Texture;
		std::vector<Entity> m_Entity;
	};

	class StaticSpriteRenderer : System {
	public:
		StaticSpriteRenderer(Signature sig, u8 id);
		~StaticSpriteRenderer();

		void Render();

	public:
		u8 m_RenderLayer = 0; // DEFAULT RENDER LAYER

	private:
		std::vector<StaticSpriteBatch*> m_Batches;
	};
}