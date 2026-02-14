#include "globals/AuroraTypes.hpp"
#include "tenshiUtil/eventsystem/EventSystem.h"

#include <SDL.h>
#include <SDL_image.h>
#include <thread>

namespace Aurora {
	class AuroraEngine {
	public:
		AuroraEngine();
		~AuroraEngine();

		void Update();
		void Render();

	public:
		// -- EVENTS
		Aurora::Event<> OnUpdate;
		Aurora::Event<> OnRender;
		Aurora::Event<> OnQuit;

		// -- THREADS
		// Handles the Rendering and the SDL Functions that have to be done in the Main Thread
		std::thread::id m_MainThreadID;

		// Handles the Update and the Input Tasks
		std::thread m_UpdateThread;

	private:
		// Thread Safe Application Run State
		std::atomic<bool> m_IsRunning = false;
	};
}