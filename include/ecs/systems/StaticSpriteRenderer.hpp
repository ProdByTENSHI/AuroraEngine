#pragma once

#include "ecs/System.h"

namespace Aurora {
	class StaticSpriteRenderer : System {
	public:
		StaticSpriteRenderer(Signature sig, u8 id);
		~StaticSpriteRenderer();

		void Render();
	};
}