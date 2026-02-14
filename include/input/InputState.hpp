#pragma once

#include <SDL.h>
#include <array>

#include "globals/AuroraTypes.hpp"

namespace Aurora {
	enum class Key : u16
	{
		// Letters
		A, B, C, D, E, F, G,
		H, I, J, K, L, M, N,
		O, P, Q, R, S, T, U,
		V, W, X, Y, Z,

		// Numbers (Top Row)
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,

		// Function Keys
		F1, F2, F3, F4,
		F5, F6, F7, F8,
		F9, F10, F11, F12,

		// Arrows
		Up,
		Down,
		Left,
		Right,

		// Control Keys
		Escape,
		Tab,
		CapsLock,
		LeftShift,
		RightShift,
		LeftCtrl,
		RightCtrl,
		LeftAlt,
		RightAlt,
		Space,
		Enter,
		Backspace,

		// Navigation
		Insert,
		Delete,
		Home,
		End,
		PageUp,
		PageDown,

		// Numpad
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		NumpadMultiply,
		NumpadAdd,
		NumpadSubtract,
		NumpadDecimal,
		NumpadDivide,
		NumpadEnter,

		// Symbols
		Tilde,
		Minus,
		Equals,
		LeftBracket,
		RightBracket,
		Backslash,
		Semicolon,
		Apostrophe,
		Comma,
		Period,
		Slash,

		// System
		PrintScreen,
		ScrollLock,
		Pause,

		// Must be the last Value
		COUNT
	};
	enum class MouseButton {
		PRIMARY = 0, // Left
		SECONDARY = 1, // Right
		WHEEL = 2, // Mouse Wheel Click
	};

	constexpr size_t KEY_COUNT = static_cast<size_t>(Key::COUNT);
	constexpr size_t MOUSE_BUTTON_COUNT = 3;

	typedef struct ButtonState {
	public:
		bool m_Down = false;
	};

	// The Input State is the complete Input State at the End of a Frame
	typedef struct InputState {
	public:
		// Keys are sorted by their ID in the Array
		std::array<ButtonState, (size_t)Key::COUNT> m_Keys = { 0 };

		// Mouse Buttons are sorted by their ID in the Array
		std::array <ButtonState, (size_t)MOUSE_BUTTON_COUNT> m_MouseButtons = { 0 };

		// Absolute Mouse Position
		u32 m_MouseX = 0;
		u32 m_MouseY = 0;

		// Mouse Dela(Relative Movement in this Frame)
		u32 m_MouseDeltaX = 0;
		u32 m_MouseDeltaY = 0;

		u32 m_MouseWheelX = 0;
		u32 m_MouseWheelY = 0;
	};
}