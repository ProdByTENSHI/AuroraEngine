#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "globals/AuroraTypes.hpp"
#include "tenshiUtil/eventsystem/EventSystem.h"

namespace Aurora {
	class Window {
	public:
		Window(charStr title, u32 w, u32 h);
		~Window();

	public:
		GLFWwindow* m_Window;
		u32 m_Width;
		u32 m_Height;

		// -- EVENTS
		Aurora::Event<u32, u32> OnResize;
	};
}