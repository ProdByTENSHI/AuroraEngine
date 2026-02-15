#pragma once

#include <SDL.h>
#include <thread>

#include "debug/Logger.hpp"
#include "ecs/ECS.h"
#include "globals/AuroraTypes.hpp"

#include "input/InputSystem.hpp"
#include "memory/ResourceManager.hpp"
#include "rendering/MasterRenderer.hpp"
#include "window/Window.hpp"

namespace Aurora {
	// -- WINDOW RELATED GLOBALS --
	inline u32 g_WindowWidth = 1280;
	inline u32 g_WindowHeight = 720;
	inline charStr g_WindowTitle = "Neko Island";
	inline u8 g_WindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;

	inline Window* g_Window = nullptr;

	// -- RENDERING
	inline std::unique_ptr<MasterRenderer> g_MasterRenderer;
	inline SDL_GLContext g_GLContext;

	// -- ECS
	inline std::unique_ptr<Ecs> g_Ecs;

	// -- MEMORY
	inline std::unique_ptr<ResourceManager> g_ResourceManager;
	inline std::thread g_ResourceThread;

	// -- INPUT
	inline std::unique_ptr<InputSystem> g_InputManager;
}