#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
		// Thread Safe Application Run State
		std::atomic<bool> m_IsRunning = false;
	};
}