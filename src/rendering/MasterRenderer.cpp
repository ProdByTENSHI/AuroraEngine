#include "rendering/MasterRenderer.hpp"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	MasterRenderer::MasterRenderer() {
		m_SpriteShader = g_ResourceManager->LoadShader("sprite");
		m_SpriteShader->Bind();

		m_TransformsSsbo.Create(sizeof(glm::mat4) * MAX_SPRITES, "Transforms");
		m_TransformsSsbo.BindToShader(*m_SpriteShader.get(), SPRITE_TRANSFORMS_SSBO_BIDING_POINT);

		m_EntityIdsUbo.Create(sizeof(i32) * MAX_SPRITES_PER_BATCH, "EntityIds");
		m_EntityIdsUbo.BindToShader(*m_SpriteShader.get(), ENTITY_IDS_UBO_BINDING_POINT);
	}

	void MasterRenderer::Render() {
		SortRenderCommandBuffer();

		// Batch together Sprites that use the same Shader and Texture
		RenderBatch _currentBatch = { 0 };
		u32 _lastTexture = 0;
		u32 _lastShader = 0;

		for (const auto& cmd : m_RenderCmdBuffer) {
			if (cmd.m_TextureId != _lastTexture || cmd.m_ShaderId != _lastShader) {
				// New batch (bind the previous one and start a new one)
				if (!_currentBatch.m_Commands.empty()) {
					m_Batches.push_back(_currentBatch);
					_currentBatch.m_Commands.clear();
				}
				_lastTexture = cmd.m_TextureId;
				_lastShader = cmd.m_ShaderId;
			}
			_currentBatch.m_Commands.push_back(cmd);
		}
		if (!_currentBatch.m_Commands.empty()) {
			m_Batches.push_back(_currentBatch); // Push the last batch
		}

		// Render
		u32 _baseOffset = 0;
		for (auto& batch : m_Batches) {
			glBindVertexArray(batch.m_Vao);

			glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 6,
				batch.m_Commands.size(), _baseOffset);
			_baseOffset += batch.m_Commands.size();
		}

		glBindVertexArray(0);
	}

	void MasterRenderer::PushRenderCommand(RenderCommand command) {
		RenderCommand _cmd = command;

		_cmd.m_SortKey = BuildSortKey(_cmd.m_Layer, _cmd.m_Depth,
			_cmd.m_ShaderId, _cmd.m_TextureId);

		m_RenderCmdBuffer.push_back(_cmd);
	}

	void MasterRenderer::SortRenderCommandBuffer() {
		std::sort(m_RenderCmdBuffer.begin(), m_RenderCmdBuffer.end());
	}
}