#include "rendering/MasterRenderer.hpp"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	MasterRenderer::MasterRenderer() {
		m_SpriteShader = g_ResourceManager->LoadShader("sprite");
		m_SpriteShader->Bind();

		m_EntityIdsSsbo.Create(sizeof(Entity) * MAX_CMD_PER_BATCH, "EntityIds");
		m_EntityIdsSsbo.BindToShader(*m_SpriteShader, ENTITY_IDS_SSBO_BINDING_POINT);

		m_TransformMatrices.Create(sizeof(glm::mat4) * MAX_CMD_PER_BATCH, "TransformMatrices");
		m_TransformMatrices.BindToShader(*m_SpriteShader, TRANSFORM_MATRICES_SSBO_BINDING_POINT);

		// -- Sprite Vertex Data
		glCreateVertexArrays(1, &m_SpriteVao);
		glBindVertexArray(m_SpriteVao);
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
		StageBufferData();

		// Render
		u32 batchStart = 0;
		for (u32 i = 1; i <= m_RenderCmdBuffer.size(); ++i) {
			// If texture changes OR we reached the end
			if (i == m_RenderCmdBuffer.size() ||
				m_RenderCmdBuffer[i].m_Texture != m_RenderCmdBuffer[batchStart].m_Texture) {
				u32 count = i - batchStart;

				auto tex = g_ResourceManager->LoadTexture(m_RenderCmdBuffer[batchStart].m_Texture);
				tex->Bind(0);

				// Use batchStart as the baseInstance
				glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 6, count, batchStart);

				batchStart = i;
			}
		}
	}

	void MasterRenderer::PushRenderCommand(RenderCommand command) {
		RenderCommand _cmd = command;

		_cmd.m_SortKey = BuildSortKey(_cmd.m_Layer, _cmd.m_Depth,
			_cmd.m_Shader, _cmd.m_Texture);

		m_RenderCmdBuffer.push_back(_cmd);
	}

	void MasterRenderer::SortRenderCommandBuffer() {
		std::sort(m_RenderCmdBuffer.begin(), m_RenderCmdBuffer.end());
	}

	void MasterRenderer::StageBufferData() {
		std::vector<glm::mat4> stagedMatrices;
		std::vector<u32> stagedEntityIds;

		stagedMatrices.reserve(m_RenderCmdBuffer.size());
		stagedEntityIds.reserve(m_RenderCmdBuffer.size());

		// Pack data into contiguous arrays based on the SORTED order
		for (const auto& cmd : m_RenderCmdBuffer) {
			stagedMatrices.push_back(cmd.m_Transform);
			stagedEntityIds.push_back(cmd.m_Entity);
		}

		// Single upload for both
		m_TransformMatrices.SubBufferData(0, stagedMatrices.size() * sizeof(glm::mat4), stagedMatrices.data());
		m_EntityIdsSsbo.SubBufferData(0, stagedEntityIds.size() * sizeof(u32), stagedEntityIds.data());
	}
}