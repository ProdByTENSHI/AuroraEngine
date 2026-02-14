#include "ecs/systems/StaticSpriteRenderer.hpp"

#include "globals/EngineGlobals.hpp"

namespace Aurora {
	StaticSpriteBatch::StaticSpriteBatch(const std::string& path)
		: m_Texture(g_ResourceManager->LoadTexture(path))
	{
	}

	StaticSpriteRenderer::StaticSpriteRenderer(Signature sig, u8 id)
		: System(sig, id)
	{
		EventHandler<Entity, Signature> OnSigChange([this]
		(Entity entity, Signature signature) {
				if ((signature & m_Signature) != m_Signature)
					return;
			});
		g_Ecs->OnEntitySignatureChange.Subscribe(OnSigChange);
	}

	StaticSpriteRenderer::~StaticSpriteRenderer() {
	}

	void StaticSpriteRenderer::Render() {
		for (u32 i = 0; i < m_Batches.size(); i++) {
		}
	}
}