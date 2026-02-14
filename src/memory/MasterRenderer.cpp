#include "rendering/MasterRenderer.hpp"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	void MasterRenderer::Render() {
		for (u32 i = 0; i < m_RenderCmdQueue.size(); i++) {
			RenderCommand _cmd = m_RenderCmdQueue.front();
			SDL_RenderCopyEx(g_Renderer, _cmd.m_Texture, &_cmd.m_SrcRect,
				&_cmd.m_DstRect, _cmd.m_Angle, NULL, _cmd.m_Flip);
			m_RenderCmdQueue.pop();
		}
	}
}