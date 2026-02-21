#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>

#include "debug/Logger.hpp"
#include "ecs/ECS.h"
#include "globals/AuroraTypes.hpp"

#include "memory/ResourceManager.hpp"
#include "rendering/MasterRenderer.hpp"
#include "window/Window.hpp"

namespace Aurora {
	// -- WINDOW RELATED GLOBALS --
	inline u32 g_WindowWidth = 1280;
	inline u32 g_WindowHeight = 720;
	inline charStr g_WindowTitle = "Neko Island";

	inline Window* g_Window = nullptr;

	// -- RENDERING
	inline std::unique_ptr<MasterRenderer> g_MasterRenderer;

	// -- ECS
	inline std::unique_ptr<Ecs> g_Ecs;

	// -- MEMORY
	inline std::unique_ptr<ResourceManager> g_ResourceManager;
	inline std::thread g_ResourceThread;

	// -- EVENTS
	inline Aurora::Event<> OnUpdate;
	inline Aurora::Event<> OnRender;
	inline Aurora::Event<> OnQuit;
}