#include "ecs/systems/SpriteRenderer.h"

#include "ecs/components/SpriteComponent.h"
#include "ecs/components/TransformComponent.h"
#include "globals/EngineGlobals.hpp"
#include "tenshiUtil/container/STLUtil.h"

namespace Aurora {
	SpriteRenderer::SpriteRenderer(Signature signature, u8 id)
		: System(signature, id) {
		EventHandler<Entity, Signature> _onSignatureChange(
			[this](Entity entity, Signature signature) {
				if (signature != m_Signature)
					return;

				TransformComponent& _transform =
					*g_Ecs->GetComponent<TransformComponent>(entity);
				SpriteComponent& _sprite =
					*g_Ecs->GetComponent<SpriteComponent>(entity);

				RenderCommand _cmd;
				_cmd.m_TextureId = _sprite.m_Texture->m_Id;
				_cmd.m_ShaderId = g_MasterRenderer->m_SpriteShader->m_Id;
				_cmd.m_PosX = _transform.m_Position.x;
				_cmd.m_PosY = _transform.m_Position.y;
				_cmd.m_Width = _transform.m_Scale.x;
				_cmd.m_Height = _transform.m_Scale.y;
				_cmd.m_Rotation = _transform.m_Rotation.x;
				_cmd.m_Layer = _sprite.m_Texture->m_Layer;

				g_MasterRenderer->PushRenderCommand(_cmd);
			});
		g_Ecs->OnEntitySignatureChange.Subscribe(_onSignatureChange);
	}

	SpriteRenderer::~SpriteRenderer() {
	}
} // namespace Aurora