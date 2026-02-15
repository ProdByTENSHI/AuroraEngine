#pragma once

#include <memory>

#include "ecs/Component.h"
#include "memory/Texture.h"

namespace Aurora
{
	class SpriteComponent : public virtual Component
	{
	public:
		SpriteComponent(std::shared_ptr<Texture> texture);

		ComponentType GetType() override;

	public:
		const std::shared_ptr<Texture> m_Texture = nullptr;
	};
}