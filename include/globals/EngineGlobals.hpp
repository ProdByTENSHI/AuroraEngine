#pragma once

#include <SDL.h>

#include "globals/AuroraTypes.hpp"
#include "debug/Logger.hpp"

#include "window/Window.hpp"

namespace Aurora {
	// -- WINDOW RELATED GLOBALS --
	inline u32 g_WindowWidth = 1280;
	inline u32 g_WindowHeight = 720;
	inline charStr g_WindowTitle = "Neko Island";
	inline u8 g_WindowFlags = SDL_WINDOW_SHOWN;

	inline Window* g_Window = nullptr;

	// -- RENDERING
	inline SDL_Renderer* g_Renderer = nullptr;
	inline u8 g_RendererFlags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;
}