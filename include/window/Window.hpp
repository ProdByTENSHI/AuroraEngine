#pragma once
#include <SDL.h>

#include "globals/AuroraTypes.hpp"
#include "tenshiUtil/eventsystem/EventSystem.h"

namespace Aurora {
	class Window {
	public:
		Window(charStr title, u32 w, u32 h, u8 flags = SDL_WINDOW_SHOWN);
		~Window();

	public:
		SDL_Window* m_Window;
		u32 m_Width;
		u32 m_Height;
		u8 m_CreationFlags;

		// -- EVENTS
		Aurora::Event<u32, u32> OnResize;

	};
}