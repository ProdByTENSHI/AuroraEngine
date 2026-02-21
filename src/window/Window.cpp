#include "window/Window.hpp"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	Window::Window(charStr title, u32 w, u32 h)
		: m_Width(w), m_Height(h)
	{
		m_Window = glfwCreateWindow(w, h, title, nullptr, nullptr);
		if (m_Window == nullptr) {
			Logger::Instance().Log("Could not create Window", LogType::Error);
		}
	}

	Window::~Window() {
		glfwDestroyWindow(m_Window);
	}
}