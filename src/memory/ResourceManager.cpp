#include "memory/ResourceManager.hpp"

#include <future>
#include <stb_image.h>
#include <string>

#include "debug/Logger.hpp"
#include "globals/EngineGlobals.hpp"
#include "tenshiUtil/container/STLUtil.h"

namespace Aurora {
	Shader* ResourceManager::LoadShader(const std::string& path)
	{
		// TODO Make Multithreaded without breaking OpenGL
		if (m_ShaderCache.find(path) != m_ShaderCache.end())
			return m_ShaderCache[path].get();

		std::shared_ptr<Shader> _shader = std::make_shared<Shader>(path);
		if (_shader == nullptr)
		{
			std::cerr << "Could not load Shader " << path << std::endl;
			return nullptr;
		}

		u32 _id = _shader->m_Id;

		m_ShaderCache[path] = _shader;
		m_ShaderTable.insert(m_ShaderTable.begin() + _id, _shader.get());

		return m_ShaderTable[_id];
	}

	Texture* ResourceManager::LoadTexture(const std::string& path)
	{
		if (m_TextureCache.find(path) != m_TextureCache.end())
			return m_TextureCache[path].get();

		std::string _loc = SPRITE_LOCATION;
		_loc += OS_SEP;
		_loc.append(path);

		std::shared_ptr<Texture> _texture = std::make_shared<Texture>(_loc);
		if (_texture == nullptr || !_texture->GetCreationStatus())
		{
			Logger::Instance().Log("Could not load Texture " + _loc,
				LogType::Error);
			return nullptr;
		}

		// Cache Texture ID since _texture is invalid after move
		u32 _id = _texture->m_Id;

		_texture->m_Name = path;
		m_TextureCache[path] = _texture;

		m_TextureTable.push_back(_texture.get());

		Logger::Instance().Log("Loaded Texture from Disk "
			+ path, LogType::Message);

		return m_TextureTable[_id];
	}

	Texture* ResourceManager::LoadTexture(u32 internalId) {
		assert(internalId < m_TextureTable.size());

		return m_TextureTable[internalId];
	}
}