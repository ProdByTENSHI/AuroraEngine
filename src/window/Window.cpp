#include "window/Window.hpp"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	Window::Window(charStr title, u32 w, u32 h, u8 flags)
		: m_Width(w), m_Height(h), m_CreationFlags(flags)
	{
		m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, w, h, flags);
		if (m_Window == nullptr) {
			Logger::Instance().Log("Could not create Window", LogType::Error);
		}
	}

	Window::~Window() {
		SDL_DestroyWindow(m_Window);
	}
}