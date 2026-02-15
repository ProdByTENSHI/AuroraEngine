#include "memory/ResourceManager.hpp"

#include <future>
#include <stb_image.h>
#include <string>

#include "debug/Logger.hpp"
#include "globals/EngineGlobals.hpp"

namespace Aurora {
	std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& path)
	{
		auto _loadFunc = [this, path]() -> std::shared_ptr<Texture> {
			if (m_Textures.find(path) != m_Textures.end())
				return m_Textures[path];

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

			m_Textures.insert(std::make_pair(path, _texture));

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
}