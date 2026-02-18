#include "ecs/systems/SpriteSheetRenderer.h"

#include "ecs/components/SpriteSheetComponent.h"
#include "ecs/components/TransformComponent.h"
#include "globals/EngineGlobals.hpp"
#include "tenshiUtil/container/STLUtil.h"

namespace Aurora {
	SpriteSheetRenderer::SpriteSheetRenderer(Signature signature, u8 id)
		: System(signature, id) {
	}

	void SpriteSheetRenderer::Render(Shader& shader) {
	}
} // namespace Aurora