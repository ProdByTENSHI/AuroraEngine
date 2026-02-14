#include "memory/ResourceManager.hpp"

#include <SDL_image.h>
#include <string>

#include "debug/Logger.hpp"
#include "globals/EngineGlobals.hpp"

namespace Aurora {
	SDL_Texture* ResourceManager::LoadTexture(const std::string& path)
	{
		auto _it = m_Textures.find(path);
		if (_it != m_Textures.end()) {
			return m_Textures[path];
		}

		std::string _finalPath = SPRITE_LOCATION;
		_finalPath += path;

		SDL_Surface* surf = IMG_Load(_finalPath.c_str());
		if (surf == nullptr) {
			Logger::Instance().Log("Could not load Image from path "
				+ _finalPath, LogType::Error);
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(g_Renderer, surf);
		if (texture == nullptr) {
			Logger::Instance().Log("Could not create Texture from Surface "
				+ _finalPath, LogType::Error);
		}

		SDL_FreeSurface(surf);

		m_Textures.insert(std::make_pair(path, texture));

		Logger::Instance().Log("Loaded Texture from Path " + _finalPath,
			LogType::Message);

		return texture;
	}
}