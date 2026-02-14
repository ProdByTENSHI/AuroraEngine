#pragma once

#include <SDL.h>
#include <memory>
#include <string>
#include <unordered_map>

#define ASSET_LOCATION "assets/"
#define SPRITE_LOCATION "assets/sprites/"

namespace Aurora {
	class ResourceManager {
	public:
		ResourceManager() {}

		// Loads Texture from SPRITE_LOCATION + path
		SDL_Texture* LoadTexture(const std::string& path);

	public:

	private:
		std::unordered_map<std::string, SDL_Texture*> m_Textures;
	};
}