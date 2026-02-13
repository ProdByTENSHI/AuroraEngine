#include "window/Window.hpp"

namespace Aurora {
	Window::Window(charStr title, u32 w, u32 h, u8 flags)
		: m_Width(w), m_Height(h), m_CreationFlags(flags)
	{
		m_WindowHandle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, w, h, flags);
	}
}