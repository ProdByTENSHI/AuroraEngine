#pragma once

#include <memory>

#include "ecs/Component.h"
#include "memory/Texture.h"

namespace Aurora
{
	class SpriteComponent : public virtual Component
	{
	public:
		SpriteComponent(Texture* texture);

		ComponentType GetType() override;

	public:
		const Texture* m_Texture = nullptr;
	};
}