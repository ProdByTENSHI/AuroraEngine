#include "core/AuroraEngine.hpp"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	AuroraEngine::AuroraEngine() {
		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			Logger::Instance().Log("Could not initialize SDL2", LogType::Error);

		if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
			Logger::Instance().Log("Could not initialize SDL Image", LogType::Error);

		g_Window = new Window(g_WindowTitle, g_WindowWidth,
			g_WindowHeight, g_WindowFlags);
		g_Renderer = SDL_CreateRenderer(g_Window->m_Window,
			-1, g_RendererFlags);

		g_MasterRenderer = std::make_unique<MasterRenderer>();
		g_Ecs = std::make_unique<Ecs>();
		g_Ecs->Init();
		g_ResourceManager = std::make_unique<ResourceManager>();

		m_IsRunning = true;
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

				case SDL_WINDOWEVENT:
					switch (e.window.event) {
					case SDL_WINDOWEVENT_RESIZED:
						i32 _w = 0;
						i32 _h = 0;

						SDL_GetWindowSize(g_Window->m_Window, &_w, &_h);
						SDL_UpdateWindowSurface(g_Window->m_Window);

						g_Window->OnResize.Dispatch(_w, _h);

						break;
					}
					break;
				}
			}

			OnUpdate.Dispatch();
		}
	}

	void AuroraEngine::Render() {
		SDL_RenderClear(Aurora::g_Renderer);

		OnRender.Dispatch();
		g_MasterRenderer->Render();

		SDL_RenderPresent(Aurora::g_Renderer);
	}
}