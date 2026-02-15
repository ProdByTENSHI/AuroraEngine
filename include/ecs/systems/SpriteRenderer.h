#pragma once

#include <vector>

#include "ecs/System.h"
#include "memory/Shader.h"
#include "rendering/SpriteBatch.h"

#include "memory/Vertex.h"

namespace Aurora
{
	class SpriteRenderer : System
	{
	public:
		SpriteRenderer(Signature signature, u8 id);
		~SpriteRenderer();

		void Render(Shader& shader);

	private:
		std::vector<SpriteBatch*> m_Batches;
	};
}