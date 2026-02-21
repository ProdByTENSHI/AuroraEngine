#include "ecs/systems/SpriteRenderer.h"

#include <glm/glm.hpp>

#include "ecs/components/SpriteComponent.h"
#include "ecs/components/TransformComponent.h"
#include "globals/EngineGlobals.hpp"
#include "tenshiUtil/container/STLUtil.h"

namespace Aurora {
	SpriteRenderer::SpriteRenderer(Signature signature, u8 id)
		: System(signature, id) {
		EventHandler<Entity, Signature> OnSignatureChangeCallback([this]
		(Entity entity, Signature sig) {
				if (sig != m_Signature)
					return;

				TransformComponent& _transform =
					*g_Ecs->GetComponent<TransformComponent>(entity);

				g_MasterRenderer->m_TransformMatrices.
					SubBufferData(sizeof(glm::mat4) * entity, sizeof(glm::mat4),
						glm::value_ptr(_transform.m_ModelMatrix));

				// Only change Transform SSBO when Entity transform has changed
				EventHandler<glm::mat4> TransformCallback([this, &_transform, entity](glm::mat4 transform) {
					g_MasterRenderer->m_TransformMatrices.
						SubBufferData(sizeof(glm::mat4) * entity, sizeof(glm::mat4),
							glm::value_ptr(transform));
					});
				_transform.OnTransformChange.Subscribe(TransformCallback);
			});

		g_Ecs->OnEntitySignatureChange.Subscribe(OnSignatureChangeCallback);

		EventHandler<> RenderCallback(
			[this]() {
				for (Entity entity : m_Entities) {
					TransformComponent& _transform =
						*g_Ecs->GetComponent<TransformComponent>(entity);
					SpriteComponent& _sprite =
						*g_Ecs->GetComponent<SpriteComponent>(entity);

					RenderCommand _cmd;
					_cmd.m_Texture = _sprite.m_Texture->m_Id;
					_cmd.m_Shader = g_MasterRenderer->m_SpriteShader->m_Id;
					_cmd.m_Layer = _sprite.m_Texture->m_Layer;
					_cmd.m_Color = ((u32)0xFF << 0,
						(u32)0xFF << 8,
						(u32)0xFF << 16,
						(u32)0xFF << 24);

					g_MasterRenderer->PushRenderCommand(_cmd);
				}
			});

		OnRender.Subscribe(RenderCallback);
	}

	SpriteRenderer::~SpriteRenderer() {
	}
} // namespace Aurora