#pragma once

#include "globals/AuroraTypes.hpp"
#include "input/InputState.hpp"

#include <mutex>
#include <thread>

namespace Aurora {
	class InputSystem {
	public:
		InputSystem();
		~InputSystem();

		// Processes the given Event by converting it to the
		// Aurora Engine intern Input State and triggering Events
		void Process(const SDL_Event& e);
		void ProcessFrameEnd();

		// At each end of a Frame the Read State takes the final Write State
		void SwapBuffers();

		bool IsKeyPressed(Key key);
		bool IsKeyHeld(Key key);
		bool IsKeyReleased(Key key);

		bool IsMouseButtonPressed(MouseButton button);
		bool IsMouseButtonHeld(MouseButton button);
		bool IsMouseButtonReleased(MouseButton button);

	public:
		// Util Function to convert SDL Keys to Engine Representation
		static Key SDLKeyToEngine(SDL_Keycode code);
		static MouseButton SDLMouseButtonToEngine(u8 code);

	public:
		InputState GetInputState();

	private:
		// Double Buffered Input State to prevent Data Races
		// or locking the State up due to read write interference
		InputState* m_WriteState;

		// When you want to read the Input State only access this
		InputState* m_ReadState;

		// Mutex to protect access to the input buffers
		mutable std::mutex m_StateMutex;
	};
}