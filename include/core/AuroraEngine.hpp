#include "globals/AuroraTypes.hpp"
#include "tenshiUtil/eventsystem/EventSystem.h"

#include <SDL.h>
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

	private:
		// Thread Safe Application Run State
		std::atomic<bool> m_IsRunning = false;

	};
}