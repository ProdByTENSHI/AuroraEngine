#pragma once

#include <GL/glew.h>
#include <array>

#include "input/InputState.hpp"

namespace Aurora {
	class InputSystem {
	public:
		InputSystem();

		// Gets called after Input Processing
		void Update();

		void SetKeyState(Key key);

		// Returns the final Input State
		// -> Processing Methods will be called before this
		InputState& GetInputState();

		std::string KeyToString(AuroraKey key);

		AuroraKey GlfwToEngineKey(i32 glfwKey);

		void SwapBuffers();

	public:
		i32 m_TotalKeyCount = 0;
		InputState* m_CurrentState;
		InputState* m_PrevState;

	private:
		static void KeyCallback(GLFWwindow* window, int key,
			int scancode, int action, int mods);

	private:
		// Seconds it takes the Key to be registered as "Hold"
		const f32 HOLD_MIN_DURATION = 0.3f;
	};
}