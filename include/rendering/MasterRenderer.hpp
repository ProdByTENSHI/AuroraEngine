#pragma once

#include <SDL.h>
#include <queue>

#include "globals/AuroraTypes.hpp"

namespace Aurora {
	constexpr u8 MAX_LAYERS = 32;

	enum class RenderLayers {
		Default = 0
	};

	struct RenderCommand {
	public:
		SDL_Rect m_SrcRect;
		SDL_Rect m_DstRect;
		SDL_Texture* m_Texture;
		f64 m_Angle;
		SDL_RendererFlip m_Flip;
		u8 m_Layer;
	};

	class MasterRenderer {
	public:
		void Render();

	public:
		// Push Render Commands to this Queue to draw them to the Screen
		std::queue<RenderCommand> m_RenderCmdQueue;

	private:
	};
}