#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "memory/Texture.h"

#define ASSET_LOCATION "assets/"
#define SPRITE_LOCATION "assets/sprites/"

namespace Aurora {
	class ResourceManager {
	public:
		ResourceManager() {}

		// Loads Texture from SPRITE_LOCATION + path
		std::shared_ptr<Texture>
			LoadTexture(const std::string& path);

	public:

	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>>
			m_Textures;
	};
}