#include "memory/ResourceManager.hpp"

#include <future>
#include <stb_image.h>
#include <string>

#include "debug/Logger.hpp"
#include "globals/EngineGlobals.hpp"

namespace Aurora {
	std::shared_ptr<Shader> ResourceManager::LoadShader(const std::string& path)
	{
		// TODO Make Multithreaded without breaking OpenGL
		if (m_ShaderCache.find(path) != m_ShaderCache.end())
			return m_ShaderCache[path];

		std::string _loc = SHADER_LOCATION;
		_loc += OS_SEP;
		_loc.append(path);
		std::shared_ptr<Shader> _shader = std::make_shared<Shader>
			(_loc + ".vert", _loc + ".frag");
		if (_shader == nullptr)
		{
			std::cerr << "Could not load Shader " << _loc << std::endl;
			return nullptr;
		}

		m_ShaderCache.insert(std::make_pair(path, _shader));
		return _shader;
	}

	std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& path)
	{
		auto _loadFunc = [this, path]() -> std::shared_ptr<Texture> {
			if (m_TextureCache.find(path) != m_TextureCache.end())
				return m_TextureCache[path];

			std::string _loc = SPRITE_LOCATION;
			_loc += OS_SEP;
			_loc.append(path);

			std::cout << _loc << std::endl;
			std::shared_ptr<Texture> _texture = std::make_shared<Texture>(_loc);
			if (_texture == nullptr || !_texture->GetCreationStatus())
			{
				Logger::Instance().Log("Could not load Texture " + _loc,
					LogType::Error);
				return nullptr;
			}

			_texture->m_Name = path;

			m_TextureCache.insert(std::make_pair(path, _texture));

			Logger::Instance().Log("Loaded Texture " + path, LogType::Message);

			return _texture;
			};

		std::promise<std::shared_ptr<Texture>> _promise;
		std::future<std::shared_ptr<Texture>> _future = _promise.get_future();

		g_ResourceThread = std::thread([promise = std::move(_promise),
			_loadFunc]() mutable
			{
				std::shared_ptr<Texture> texture = _loadFunc();
				promise.set_value(texture);
			});
		std::shared_ptr<Texture> loadedTexture = _future.get();

		g_ResourceThread.join();

		return loadedTexture;
	}

	std::shared_ptr<Texture> ResourceManager::LoadTexture(u32 internalId) {
		for (auto t : m_TextureCache) {
			if (t.second->m_Id == internalId)
				return t.second;
		}

		return nullptr;
	}
}