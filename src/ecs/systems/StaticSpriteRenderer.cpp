#include "ecs/components/StaticSpriteComponent.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/systems/StaticSpriteRenderer.hpp"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	StaticSpriteRenderer::StaticSpriteRenderer(Signature sig, u8 id)
		: System(sig, id)
	{
		EventHandler<Entity, Signature> OnSigChange([this]
		(Entity entity, Signature signature) {
				if ((signature & m_Signature) == m_Signature) {
					StaticSpriteComponent& _sprite = *g_Ecs->GetComponent
						<StaticSpriteComponent>(entity);

					// Add to Batch if there is already one with the same Texture
					for (u32 i = 0; i < m_Batches.size(); i++) {
						if (m_Batches[i]->m_Texture != _sprite.m_Texture)
							continue;

						m_Batches[i]->m_Entity.push_back(entity);
						return;
					}

					StaticSpriteBatch* batch = new StaticSpriteBatch();
					batch->m_Texture = _sprite.m_Texture;
					batch->m_Entity.push_back(entity);

					m_Batches.push_back(batch);
				}
				// TODO: Implement Entity removal Case
			});
		g_Ecs->OnEntitySignatureChange.Subscribe(OnSigChange);
	}

	StaticSpriteRenderer::~StaticSpriteRenderer() {
	}

	void StaticSpriteRenderer::Render() {
		for (u32 i = 0; i < m_Batches.size(); i++) {
			for (u32 y = 0; y < m_Batches[i]->m_Entity.size(); y++) {
				auto entity = m_Batches[i]->m_Entity[y];

				RenderCommand _cmd = { 0 };
				StaticSpriteComponent& _sprite = *g_Ecs->GetComponent<StaticSpriteComponent>
					(entity);
				TransformComponent& _transform = *g_Ecs->GetComponent<TransformComponent>
					(entity);

				_cmd.m_Layer = _sprite.m_RenderLayer;
				_cmd.m_Texture = _sprite.m_Texture;
				_cmd.m_DstRect = _transform.ToSDLRect();

				g_MasterRenderer->m_RenderCmdQueue.push(_cmd);
			}
		}
	}
}