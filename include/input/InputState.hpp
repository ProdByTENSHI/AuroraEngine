#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>

#include "globals/AuroraTypes.hpp"

namespace Aurora {
	enum class AuroraKey : int {
		// --- Printable Keys (GLFW 32 - 162) ---
		Space = 0,   // GLFW_KEY_SPACE (32)
		Apostrophe = 7,   // 39
		Comma = 12,  // 44
		Minus = 13,  // 45
		Period = 14,  // 46
		Slash = 15,  // 47
		Zero = 16,  // 48
		One = 17,  // 49
		Two = 18,  // 50
		Three = 19,  // 51
		Four = 20,  // 52
		Five = 21,  // 53
		Six = 22,  // 54
		Seven = 23,  // 55
		Eight = 24,  // 56
		Nine = 25,  // 57
		Semicolon = 27,  // 59
		Equal = 29,  // 61
		A = 33,  // 65
		B = 34,
		C = 35,
		D = 36,
		E = 37,
		F = 38,
		G = 39,
		H = 40,
		I = 41,
		J = 42,
		K = 43,
		L = 44,
		M = 45,
		N = 46,
		O = 47,
		P = 48,
		Q = 49,
		R = 50,
		S = 51,
		T = 52,
		U = 53,
		V = 54,
		W = 55,
		X = 56,
		// QWERTZ
		Y = 58,
		Z = 57,
		LeftBracket = 59,  // 91
		Backslash = 60,  // 92
		RightBracket = 61,  // 93
		GraveAccent = 64,  // 96
		World1 = 129, // 161
		World2 = 130, // 162

		// --- Function/Special Keys (GLFW 256 - 348) ---
		// Note: There is a "gap" in indices here to maintain O(1) mapping.
		Escape = 224, // 256 - 32
		Enter = 225, // 257
		Tab = 226,
		Backspace = 227,
		Insert = 228,
		Delete = 229,
		Right = 230,
		Left = 231,
		Down = 232,
		Up = 233,
		PageUp = 234,
		PageDown = 235,
		Home = 236,
		End = 237,
		CapsLock = 248,
		ScrollLock = 249,
		NumLock = 250,
		PrintScreen = 251,
		Pause = 252,
		F1 = 258,
		F2 = 259,
		F3 = 260,
		F4 = 261,
		F5 = 262,
		F6 = 263,
		F7 = 264,
		F8 = 265,
		F9 = 266,
		F10 = 267,
		F11 = 268,
		F12 = 269,
		F13 = 270,
		F14 = 271,
		F15 = 272,
		F16 = 273,
		F17 = 274,
		F18 = 275,
		F19 = 276,
		F20 = 277,
		F21 = 278,
		F22 = 279,
		F23 = 280,
		F24 = 281,
		F25 = 282,
		KP_0 = 288, // Keypad 0
		KP_1 = 289,
		KP_2 = 290,
		KP_3 = 291,
		KP_4 = 292,
		KP_5 = 293,
		KP_6 = 294,
		KP_7 = 295,
		KP_8 = 296,
		KP_9 = 297,
		KP_Decimal = 298,
		KP_Divide = 299,
		KP_Multiply = 300,
		KP_Subtract = 301,
		KP_Add = 302,
		KP_Enter = 303,
		KP_Equal = 304,
		LeftShift = 308,
		LeftControl = 309,
		LeftAlt = 310,
		LeftSuper = 311,
		RightShift = 312,
		RightControl = 313,
		RightAlt = 314,
		RightSuper = 315,
		Menu = 316,

		Count = 317,  // Use this to size your vector
		INVALID = 0xFF
	};

	enum class KeyState : int {
		Release = 0,
		Press = 1,
		Repeat = 2,
		Hold = 3,
		NONE = 0xFF
	};

	struct Key {
	public:
		// GLFW Key Code
		AuroraKey m_Key = AuroraKey::A;

		KeyState m_State = KeyState::NONE;	// Press = 0, Release = 1, Hold = 2

		// Duration the Key is pressed down -> Resets after Release
		f32 m_Duration = 0.0f;
	};

	struct InputState {
		// Key Look Up Table
		std::vector<Key> m_Keys;
	};
}