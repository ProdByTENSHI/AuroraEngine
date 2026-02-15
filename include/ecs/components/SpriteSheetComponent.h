#pragma once

#include "ecs/Component.h"
#include "memory/SpriteSheet.h"
#include "tenshiUtil/eventsystem/EventSystem.h"

namespace Aurora
{
	class SpriteSheetComponent : public virtual Component
	{
	public:
		SpriteSheetComponent();
		explicit SpriteSheetComponent(std::shared_ptr<SpriteSheet> spriteSheet);

		ComponentType GetType() override;

		void SetFrame(u32 frame);

	public:
		std::shared_ptr<SpriteSheet> m_SpriteSheet = nullptr;
		u32 m_CurrentFrame = 0;

		Event<u32, u32> m_OnFrameChange;
	};
}