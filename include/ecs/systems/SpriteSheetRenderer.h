#pragma once

#include <vector>

#include "ecs/System.h"
#include "memory/Shader.h"
#include "rendering/SpriteSheetBatch.h"

namespace Aurora {
	class SpriteSheetRenderer : public System {
	public:
		SpriteSheetRenderer(Signature signature, u8 id);

		void Render(Shader& shader);

	private:
		std::vector<SpriteSheetBatch*> m_Batches;
	};
} // namespace Aurora
