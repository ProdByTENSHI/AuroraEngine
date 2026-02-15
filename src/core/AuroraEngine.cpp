#include "core/AuroraEngine.hpp"

#include "globals/EngineGlobals.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <sstream>

#include <GL/glew.h>

namespace Aurora {
	void glewMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
		GLsizei length, GLchar const* message,
		void const* user_param) {
		auto const src_str = [source]() {
			switch (source) {
			case GL_DEBUG_SOURCE_API:
				return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				return "WINDOW SYSTEM";
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				return "SHADER COMPILER";
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				return "THIRD PARTY";
			case GL_DEBUG_SOURCE_APPLICATION:
				return "APPLICATION";
			case GL_DEBUG_SOURCE_OTHER:
				return "OTHER";
			}
			}();

		auto const type_str = [type]() {
			switch (type) {
			case GL_DEBUG_TYPE_ERROR:
				return "ERROR";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				return "DEPRECATED_BEHAVIOR";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				return "UNDEFINED_BEHAVIOR";
			case GL_DEBUG_TYPE_PORTABILITY:
				return "PORTABILITY";
			case GL_DEBUG_TYPE_PERFORMANCE:
				return "PERFORMANCE";
			case GL_DEBUG_TYPE_MARKER:
				return "MARKER";
			case GL_DEBUG_TYPE_OTHER:
				return "OTHER";
			}
			}();

		auto const severity_str = [severity]() {
			switch (severity) {
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				return "NOTIFICATION";
			case GL_DEBUG_SEVERITY_LOW:
				return "LOW";
			case GL_DEBUG_SEVERITY_MEDIUM:
				return "MEDIUM";
			case GL_DEBUG_SEVERITY_HIGH:
				return "HIGH";
			}
			}();

		std::stringstream _output;
		_output << src_str << ", " << type_str << ", " << severity_str << ", " << id
			<< ": " << message << '\n';

		Logger::Instance().Log(_output.str());
	}

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
		GLenum _glInit = glewInit();
		if (_glInit != GLEW_OK) {
			std::cerr << "Could not initialize Glew. Error: " << glewGetErrorString(_glInit) << std::endl;
			return;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(glewMessageCallback, nullptr);

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