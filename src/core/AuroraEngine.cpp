#include "core/AuroraEngine.hpp"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	AuroraEngine::AuroraEngine() {
		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			Logger::Instance().Log("Could not initialize SDL2", LogType::Error);

		g_Window = new Window(g_WindowTitle, g_WindowWidth, 
			g_WindowHeight, g_WindowFlags);
		g_Renderer = SDL_CreateRenderer(g_Window->m_Window, 
			-1, g_RendererFlags);

		m_IsRunning = true;
		Update();
	}

	AuroraEngine::~AuroraEngine() {
		SDL_DestroyRenderer(g_Renderer);
		delete g_Window;
	}

	void AuroraEngine::Update() {
		while (m_IsRunning) {
			// Process Event Queue before Updating
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				switch (e.type) {
				case SDL_QUIT:
					m_IsRunning = false;
					break;
				}
			}

			OnUpdate.Dispatch();
		}
	}

	void AuroraEngine::Render() {
		SDL_RenderClear(Aurora::g_Renderer);

		OnRender.Dispatch();

		SDL_RenderPresent(Aurora::g_Renderer);
	}
}