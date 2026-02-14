#pragma once

#include "ecs/System.h"

#include <SDL.h>
#include <vector>

namespace Aurora {
	// Internally sorts the Entities by their Textures to minimize Texture Dereferencing
	typedef struct StaticSpriteBatch {
	public:
		explicit StaticSpriteBatch(const std::string& path);

		std::vector<Entity> m_Entities;
		const SDL_Texture* m_Texture;
	};

	class StaticSpriteRenderer : System {
	public:
		StaticSpriteRenderer(Signature sig, u8 id);
		~StaticSpriteRenderer();

		void Render();

	public:
		u8 m_RenderLayer = 0; // DEFAULT RENDER LAYER

	private:
		std::vector<StaticSpriteBatch> m_Batches;
	};
}