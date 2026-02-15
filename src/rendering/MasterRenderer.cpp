#include "rendering/MasterRenderer.hpp"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	void MasterRenderer::Render() {
		SortRenderCommandBuffer();
	}

	void MasterRenderer::PushRenderCommand(RenderCommand command) {
		RenderCommand _cmd = command;

		_cmd.m_SortKey = BuildSortKey(_cmd.m_Layer, _cmd.m_Depth,
			_cmd.m_ShaderId, _cmd.m_TextureId);

		Logger::Instance().Log("Sort Key " + std::to_string(_cmd.m_SortKey));

		m_RenderCmdBuffer.push_back(_cmd);
	}

	void MasterRenderer::SortRenderCommandBuffer() {
		std::sort(m_RenderCmdBuffer.begin(), m_RenderCmdBuffer.end());
	}
}