#include "ecs/components/SpriteSheetComponent.h"

namespace Aurora {
	SpriteSheetComponent::SpriteSheetComponent() {}

	SpriteSheetComponent::SpriteSheetComponent(
		std::shared_ptr<SpriteSheet> spriteSheet)
		: m_SpriteSheet(spriteSheet) {
	}

	void SpriteSheetComponent::SetFrame(u32 frame) {
		u32 _oldFrame = m_CurrentFrame;
		m_CurrentFrame = frame;
		m_OnFrameChange.Dispatch(_oldFrame, m_CurrentFrame);
	}

	ComponentType SpriteSheetComponent::GetType() {
		return ComponentType::SpriteSheetType;
	}
} // namespace Aurora