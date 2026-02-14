#pragma once

#include "ecs/Component.h"

#include <SDL.h>
#include <memory>
#include <string>

namespace Aurora {
	class StaticSpriteComponent : public virtual Component {
	public:
		explicit StaticSpriteComponent(const char* path);

		void LoadSprite(const char* path);

		// If you want to render a Sprite from a Spritesheet you can
		// supply Data from
		// Set once
		// col: Column(0 to cols - 1). Columns and Rows are calculated
		// by equally splitting the Texture into evenly sized Tiles
		// and assigning the col and row id from the top left to the bottom right
		// row: Row(0 to rows - 1)
		// colNum: Number of Columns
		// rowNum: Number of Rows
		void SetSpriteSheetData(u32 col, u32 row, u32 colNum, u32 rowNum);

		ComponentType GetType() override;

	public:
		SDL_Texture* m_Texture;
		u8 m_RenderLayer = 0; // DEFAULT LAYER
	};
}