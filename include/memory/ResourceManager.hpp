#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "memory/Shader.h"
#include "memory/Texture.h"

#define ASSET_LOCATION "assets/"
#define SPRITE_LOCATION "assets/sprites/"
#define SHADER_LOCATION "assets/shader/"

namespace Aurora {
	class ResourceManager {
	public:
		ResourceManager() {}

		std::shared_ptr<Shader> LoadShader(const std::string& path);

		// Loads Texture from SPRITE_LOCATION + path
		std::shared_ptr<Texture>
			LoadTexture(const std::string& path);

		std::shared_ptr<Texture>
			LoadTexture(u32 internalId);

	public:

	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>>
			m_TextureCache;
		std::unordered_map<std::string, std::shared_ptr<Shader>>
			m_ShaderCache;
	};
}