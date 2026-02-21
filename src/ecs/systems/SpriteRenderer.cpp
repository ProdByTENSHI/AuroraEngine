#include "ecs/systems/SpriteRenderer.h"

#include <glm/glm.hpp>

#include "ecs/components/SpriteComponent.h"
#include "ecs/components/TransformComponent.h"
#include "globals/EngineGlobals.hpp"
#include "tenshiUtil/container/STLUtil.h"

namespace Aurora {
	SpriteRenderer::SpriteRenderer(Signature signature, u8 id)
		: System(signature, id) {
		EventHandler<> RenderCallback(
			[this]() {
				for (Entity entity : m_Entities) {
					TransformComponent& _transform =
						*g_Ecs->GetComponent<TransformComponent>(entity);
					SpriteComponent& _sprite =
						*g_Ecs->GetComponent<SpriteComponent>(entity);

					RenderCommand _cmd;
					_cmd.m_Entity = entity;
					_cmd.m_Texture = _sprite.m_Texture->m_Id;
					_cmd.m_Shader = g_MasterRenderer->m_SpriteShader->m_Id;
					_cmd.m_Layer = _sprite.m_Texture->m_Layer;
					_cmd.m_Color = ((u32)0xFF << 0,
						(u32)0xFF << 8,
						(u32)0xFF << 16,
						(u32)0xFF << 24);
					_cmd.m_Transform = _transform.m_ModelMatrix;

					g_MasterRenderer->PushRenderCommand(_cmd);
				}
			});

		OnRender.Subscribe(RenderCallback);
	}

	SpriteRenderer::~SpriteRenderer() {
	}
} // namespace Aurora