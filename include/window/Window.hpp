#pragma once
#include <SDL.h>

#include "globals/AuroraTypes.hpp"

namespace Aurora {
	class Window {
	public:
		Window(charStr title, u32 w, u32 h, u8 flags = SDL_WINDOW_SHOWN);
		~Window();

	protected:
		u32 m_Width;
		u32 m_Height;

		u8 m_CreationFlags;

		SDL_Window* m_WindowHandle;
	};
}