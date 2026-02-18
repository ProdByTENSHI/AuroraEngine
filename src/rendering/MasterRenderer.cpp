#include "rendering/MasterRenderer.hpp"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	MasterRenderer::MasterRenderer() {
		m_SpriteShader = g_ResourceManager->LoadShader("sprite");
		m_SpriteShader->Bind();

		m_EntityIdsUbo.Create(sizeof(i32) * MAX_SPRITES_PER_BATCH, "EntityIds");
		m_EntityIdsUbo.BindToShader(*m_SpriteShader.get(), ENTITY_IDS_UBO_BINDING_POINT);

		// -- Sprite Vertex Data
		glCreateVertexArrays(1, &m_SpriteVao);
		glCreateBuffers(1, &m_SpriteVbo);

		glNamedBufferStorage(m_SpriteVbo, 6 * sizeof(Vertex),
			QUAD_VERTICES, GL_DYNAMIC_STORAGE_BIT);

		glEnableVertexArrayAttrib(m_SpriteVao, 0);
		glVertexArrayAttribFormat(m_SpriteVao, 0, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_SpriteVao, 0, 0);
		glVertexArrayVertexBuffer(m_SpriteVao, 0, m_SpriteVbo, 0,
			sizeof(Vertex));

		// Texture Slots
		glActiveTexture(GL_TEXTURE0);
	}

	void MasterRenderer::Render() {
		SortRenderCommandBuffer();

		// Batch together Sprites that use the same Shader and Texture
		RenderBatch _currentBatch = { 0 };
		std::shared_ptr<Texture> _lastTexture;
		std::shared_ptr<Shader> _lastShader;

		for (const auto& cmd : m_RenderCmdBuffer) {
			if (cmd.m_Texture.get() != _lastTexture.get()
				|| cmd.m_Shader.get() != _lastShader.get()) {
				// New batch (bind the previous one and start a new one)
				if (!_currentBatch.m_Commands.empty()) {
					m_Batches.push_back(_currentBatch);
					_currentBatch.m_Commands.clear();
				}
				_lastTexture = cmd.m_Texture;
				_lastShader = cmd.m_Shader;
			}
			_currentBatch.m_Commands.push_back(cmd);
		}
		if (!_currentBatch.m_Commands.empty()) {
			m_Batches.push_back(_currentBatch); // Push the last batch
		}

		// Render

		u32 _baseOffset = 0;
		for (auto& batch : m_Batches) {
			glBindTexture(GL_TEXTURE_2D, batch.m_Texture);
			glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 6,
				batch.m_Commands.size(), _baseOffset);
			_baseOffset += batch.m_Commands.size();
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	void MasterRenderer::PushRenderCommand(RenderCommand command) {
		RenderCommand _cmd = command;

		_cmd.m_SortKey = BuildSortKey(_cmd.m_Layer, _cmd.m_Depth,
			_cmd.m_Shader->m_Id, _cmd.m_Texture->m_Id);

		m_RenderCmdBuffer.push_back(_cmd);
	}

	void MasterRenderer::SortRenderCommandBuffer() {
		std::sort(m_RenderCmdBuffer.begin(), m_RenderCmdBuffer.end());
	}
}