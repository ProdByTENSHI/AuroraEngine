#pragma once

#include <memory>
#include <queue>

#include "globals/AuroraTypes.hpp"
#include "tenshiUtil/memory/Ssbo.h"
#include "tenshiUtil/memory/UniformBuffer.h"

namespace Aurora {
	constexpr u8 MAX_LAYERS = 32;

	enum class RenderLayers {
		Default = 0
	};

	struct RenderCommand {
	public:
		u8 m_Layer = 0;
	};

	class MasterRenderer {
	public:
		void Render();

	public:
		// Push Render Commands to this Queue to draw them to the Screen
		std::queue<RenderCommand> m_RenderCmdQueue;

		Ssbo m_TransformsSsbo;
		UniformBuffer m_EntityIdsUbo;

	private:
		std::shared_ptr<Shader> m_SpriteShader = nullptr;
	};
}