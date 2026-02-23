#include "input/InputSystem.hpp"

#include "globals/EngineGlobals.hpp"

#include <utility>

namespace Aurora {
	InputSystem::InputSystem() {
		glfwSetKeyCallback(g_Window->m_Window, KeyCallback);

		m_CurrentState = new InputState{};
		m_PrevState = new InputState{};

		m_TotalKeyCount = (i32)AuroraKey::Count;
		m_CurrentState->m_Keys.resize(m_TotalKeyCount);
		m_PrevState->m_Keys.resize(m_TotalKeyCount);

		// Initialize the keys so they know who they are
		for (i32 i = 0; i < m_TotalKeyCount; i++) {
			m_CurrentState->m_Keys[i].m_Key = (AuroraKey)i;
			m_PrevState->m_Keys[i].m_Key = (AuroraKey)i;
		}
	}

	void InputSystem::Update() {
		// Update Key press durations
		for (i32 i = 0; i < m_TotalKeyCount; i++) {
			auto& _key = m_CurrentState->m_Keys[i];
			auto& _prevKey = m_PrevState->m_Keys[i];

			// 1. Detection: Key was JUST released
			if (_prevKey.m_State != KeyState::Release && _key.m_State == KeyState::Release) {
				_key.m_Duration = 0;
				Logger::Instance().Log(KeyToString(_key.m_Key) + " was Released");
				continue;
			}

			// 2. Detection: Key is currently being active
			if (_key.m_State == KeyState::Press || _key.m_State == KeyState::Hold) {
				_key.m_Duration += g_DeltaTime;

				// Only log "pressed" on the very first frame it happens
				if (_prevKey.m_State == KeyState::Release) {
					Logger::Instance().Log(KeyToString(_key.m_Key) + " was Pressed");
				}

				// 3. Transition to Hold state
				if (_key.m_Duration >= HOLD_MIN_DURATION && _key.m_State != KeyState::Hold) {
					_key.m_State = KeyState::Hold;
					Logger::Instance().Log(KeyToString(_key.m_Key) + " is now being HELD");
				}
			}
		}
	}

	void InputSystem::SetKeyState(Key key) {
		m_CurrentState->m_Keys[(u32)key.m_Key] = key;
	}

	void InputSystem::KeyCallback(GLFWwindow* window, int key, int scancode,
		int action, int mods) {
		if (key < 32 || key > 348) return;

		int index = key - 32;

		KeyState _state = KeyState::Release;
		if (action == GLFW_PRESS)   _state = KeyState::Press;
		if (action == GLFW_REPEAT)  _state = KeyState::Repeat;

		g_InputSystem->m_CurrentState->m_Keys[index].m_State = _state;
	}

	void InputSystem::SwapBuffers() {
		// 1. Point the 'Previous' to what was just 'Current'
		// 2. Point the 'Current' to the old 'Previous'
		std::swap(m_CurrentState, m_PrevState);

		// 3. IMPORTANT: Copy the state from Previous to Current
		// We do this because if a key was "Hold" last frame,
		// it is still "Hold" this frame until a callback says otherwise.
		*m_CurrentState = *m_PrevState;
	}

	std::string InputSystem::KeyToString(AuroraKey key) {
		switch (key) {
			// --- Printable Keys ---
		case AuroraKey::Space:         return "Space";
		case AuroraKey::Apostrophe:    return "Apostrophe";
		case AuroraKey::Comma:         return "Comma";
		case AuroraKey::Minus:         return "Minus";
		case AuroraKey::Period:        return "Period";
		case AuroraKey::Slash:         return "Slash";
		case AuroraKey::Zero:          return "0";
		case AuroraKey::One:           return "1";
		case AuroraKey::Two:           return "2";
		case AuroraKey::Three:         return "3";
		case AuroraKey::Four:          return "4";
		case AuroraKey::Five:          return "5";
		case AuroraKey::Six:           return "6";
		case AuroraKey::Seven:         return "7";
		case AuroraKey::Eight:         return "8";
		case AuroraKey::Nine:          return "9";
		case AuroraKey::Semicolon:     return "Semicolon";
		case AuroraKey::Equal:         return "Equal";
		case AuroraKey::A:             return "A";
		case AuroraKey::B:             return "B";
		case AuroraKey::C:             return "C";
		case AuroraKey::D:             return "D";
		case AuroraKey::E:             return "E";
		case AuroraKey::F:             return "F";
		case AuroraKey::G:             return "G";
		case AuroraKey::H:             return "H";
		case AuroraKey::I:             return "I";
		case AuroraKey::J:             return "J";
		case AuroraKey::K:             return "K";
		case AuroraKey::L:             return "L";
		case AuroraKey::M:             return "M";
		case AuroraKey::N:             return "N";
		case AuroraKey::O:             return "O";
		case AuroraKey::P:             return "P";
		case AuroraKey::Q:             return "Q";
		case AuroraKey::R:             return "R";
		case AuroraKey::S:             return "S";
		case AuroraKey::T:             return "T";
		case AuroraKey::U:             return "U";
		case AuroraKey::V:             return "V";
		case AuroraKey::W:             return "W";
		case AuroraKey::X:             return "X";
		case AuroraKey::Y:             return "Y";
		case AuroraKey::Z:             return "Z";
		case AuroraKey::LeftBracket:   return "Left Bracket";
		case AuroraKey::Backslash:     return "Backslash";
		case AuroraKey::RightBracket:  return "Right Bracket";
		case AuroraKey::GraveAccent:   return "Grave Accent";

			// --- Navigation & Control ---
		case AuroraKey::Escape:        return "Escape";
		case AuroraKey::Enter:         return "Enter";
		case AuroraKey::Tab:           return "Tab";
		case AuroraKey::Backspace:     return "Backspace";
		case AuroraKey::Insert:        return "Insert";
		case AuroraKey::Delete:        return "Delete";
		case AuroraKey::Right:         return "Right Arrow";
		case AuroraKey::Left:          return "Left Arrow";
		case AuroraKey::Down:          return "Down Arrow";
		case AuroraKey::Up:            return "Up Arrow";
		case AuroraKey::PageUp:        return "Page Up";
		case AuroraKey::PageDown:      return "Page Down";
		case AuroraKey::Home:          return "Home";
		case AuroraKey::End:           return "End";

			// --- Modifiers ---
		case AuroraKey::LeftShift:     return "Left Shift";
		case AuroraKey::LeftControl:   return "Left Control";
		case AuroraKey::LeftAlt:       return "Left Alt";
		case AuroraKey::RightShift:    return "Right Shift";
		case AuroraKey::RightControl:  return "Right Control";
		case AuroraKey::RightAlt:      return "Right Alt";

			// --- Function Keys ---
		case AuroraKey::F1:            return "F1";
		case AuroraKey::F2:            return "F2";
		case AuroraKey::F3:            return "F3";
		case AuroraKey::F4:            return "F4";
		case AuroraKey::F5:            return "F5";
		case AuroraKey::F12:           return "F12";

		default:                       return "Unknown Key";
		}
	}
}