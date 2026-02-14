#include "ecs/systems/StaticSpriteRenderer.hpp"

namespace Aurora {
	StaticSpriteRenderer::StaticSpriteRenderer(Signature sig, u8 id)
		: System(sig, id)
	{
	}

	StaticSpriteRenderer::~StaticSpriteRenderer() {
	}

	void StaticSpriteRenderer::Render() {
	}
}