#include "core/AuroraEngine.hpp"

#include "globals/EngineGlobals.hpp"
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <sstream>

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
		// Initialize GLFW
		if (glfwInit() == GLFW_FALSE)
			Logger::Instance().Log("Could not initialize GLFW", LogType::Error);

		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		g_Window = new Window(g_WindowTitle, g_WindowWidth,
			g_WindowHeight);

		glfwMakeContextCurrent(g_Window->m_Window);

		printf("GL Version: %s\n", glGetString(GL_VERSION));
		printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

		glfwSwapInterval(1); // Enable VSync

		// Initialize OpenGL Glew
		GLenum _glInit = glewInit();
		if (_glInit != GLEW_OK) {
			std::cerr << "Could not initialize Glew. Error: " << glewGetErrorString(_glInit) << std::endl;
			return;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(glewMessageCallback, nullptr);

		glViewport(0, 0, g_WindowWidth, g_WindowHeight);

		g_ResourceManager = std::make_unique<ResourceManager>();
		g_MasterRenderer = std::make_unique<MasterRenderer>();
		g_Ecs = std::make_unique<Ecs>();
		g_Ecs->Init();

		m_IsRunning = true;
	}

	AuroraEngine::~AuroraEngine() {
		delete g_Window;
	}

	void AuroraEngine::Update() {
		while (m_IsRunning) {
			// Process Event Queue before Updating
			// This must be done in the Main Thread

			glfwPollEvents();

			OnUpdate.Dispatch();

			Render();
		}
	}

	void AuroraEngine::Render() {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		OnRender.Dispatch();
		g_MasterRenderer->Render();

		glfwSwapBuffers(g_Window->m_Window);
	}
}