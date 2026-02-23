#include "globals/AuroraTypes.hpp"
#include "tenshiUtil/eventsystem/EventSystem.h"

#include <thread>

namespace Aurora {
	class AuroraEngine {
	public:
		AuroraEngine();
		~AuroraEngine();

		void Update();
		void Render();

	private:
		void HandleEngineEvents();

	private:
		// Thread Safe Application Run State
		std::atomic<bool> m_IsRunning = false;
	};
}