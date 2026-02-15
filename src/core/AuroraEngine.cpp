#include "core/AuroraEngine.hpp"

#include "globals/EngineGlobals.hpp"

#include <GL/glew.h>

namespace Aurora {
	AuroraEngine::AuroraEngine() {
		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			Logger::Instance().Log("Could not initialize SDL2", LogType::Error);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
			SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);

		g_Window = new Window(g_WindowTitle, g_WindowWidth,
			g_WindowHeight, g_WindowFlags);

		g_GLContext = SDL_GL_CreateContext(g_Window->m_Window);

		SDL_GL_SetSwapInterval(1); // Enable VSync

		// Initialize OpenGL Glew
		glewInit();

		glViewport(0, 0, g_WindowWidth, g_WindowHeight);

		g_MasterRenderer = std::make_unique<MasterRenderer>();
		g_Ecs = std::make_unique<Ecs>();
		g_Ecs->Init();
		g_ResourceManager = std::make_unique<ResourceManager>();
		g_InputManager = std::make_unique<InputSystem>();

		m_IsRunning = true;
	}

	AuroraEngine::~AuroraEngine() {
		delete g_Window;
	}

	void AuroraEngine::Update() {
		while (m_IsRunning) {
			g_InputManager->SwapBuffers();

			// Process Event Queue before Updating
			// This must be done in the Main Thread
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				// -- APPLICATION EVENTS --
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
						glViewport(0, 0, _w, _h);

						g_Window->OnResize.Dispatch(_w, _h);

						break;
					}
					break;
				}

				// -- OTHER --
				g_InputManager->Process(e);
			}

			OnUpdate.Dispatch();

			Render();
		}
	}

	void AuroraEngine::Render() {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		OnRender.Dispatch();
		g_MasterRenderer->Render();

		SDL_GL_SwapWindow(g_Window->m_Window);
	}
}