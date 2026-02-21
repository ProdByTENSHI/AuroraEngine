#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "globals/EngineConstants.hpp"
#include "memory/Shader.h"
#include "memory/Texture.h"

namespace Aurora {
	class ResourceManager {
	public:

		ResourceManager() { m_TextureTable.reserve(1000); m_ShaderTable.reserve(50); }

		Shader* LoadShader(const std::string& path);

		// Loads Texture from SPRITE_LOCATION + path
		Texture* LoadTexture(const std::string& path);

		// Load Texture from ID(More Cache friendly but fails if Texture wasnt cached before)
		Texture* LoadTexture(u32 internalId);

	public:

	private:
		// Unordered Map own Resources -> Raw Pointer are passed around
		std::unordered_map<std::string, std::shared_ptr<Texture>>
			m_TextureCache;
		std::unordered_map<std::string, std::shared_ptr<Shader>>
			m_ShaderCache;

		// -- Used for Look Ups(More cache friendly)
		std::vector<Texture*> m_TextureTable;
		std::vector<Shader*> m_ShaderTable;
	};
}