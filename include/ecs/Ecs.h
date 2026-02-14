#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <type_traits>

#include "debug/Logger.hpp"
#include "ecs/Component.h"
#include "ecs/ComponentArray.h"
#include "ecs/ECS_Definitions.h"
#include "ecs/System.h"
#include "globals/AuroraTypes.hpp"
#include "tenshiUtil/eventsystem/EventSystem.h"

#include "ecs/systems/StaticSpriteRenderer.hpp"

namespace Aurora
{
	// -- SYSTEMS ID ORDER
	constexpr u32 STATIC_SPRITE_RENDERER_ID = 0;

	template <typename Derived>
	concept IsBaseOfComponent = std::is_base_of<Component, Derived>::value;
	template <typename Derived>
	concept IsBaseOfSystem = std::is_base_of<System, Derived>::value;

	class Ecs
	{
	public:
		Ecs();
		~Ecs();

		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		void Init();
		void DestroyAllEntities();

		bool IsEntityValid(Entity entity);

		// Returns the ID of the Entity on the given Position
		// [in] screenSpacePosition: Position in Format [0,0] - [windowWidth,
		// windowHeight]
		// [return] Entity: Returns either an Entity ID or INVALID_ENTITY if none was
		// found
		// IMPORTANT! Use Position that considers the Camera Matrices
		Entity GetEntityOnPosition(const glm::vec2& screenSpacePos);

	public:
		template <IsBaseOfComponent T>
		void AddComponent(Entity entity, T& component)
		{
			ComponentType _type = component.GetType();
			if (_type == ComponentType::InvalidType)
			{
				std::cout << "[ECS] Cannot add Base Component to Entity " << entity
					<< std::endl;
				return;
			}

			const char* _typeName = typeid(T).name();
			if (m_ComponentArrays.find(_typeName) == m_ComponentArrays.end())
				m_ComponentArrays.insert(
					std::make_pair(_typeName, new ComponentArray<T>()));

			m_ComponentArrays[_typeName]->m_EntityToComponent.insert(
				std::make_pair(entity, &component));
			m_EntitySignatures[entity].set(_type);
			OnEntitySignatureChange.Dispatch(entity, m_EntitySignatures[entity]);

			std::string _msg = "Added Component ";
			_msg.append(_typeName).append(" to Entity ")
				.append(std::to_string(entity));
			Logger::Instance().Log(_msg);
		}

		template <IsBaseOfComponent T>
		void RemoveComponent(Entity entity, ComponentType type)
		{
			m_ComponentArrays[typeid(T).name()]->m_EntityToComponent.erase(entity);
			m_EntitySignatures[entity].set(type, false);
			OnEntitySignatureChange.Dispatch(entity, m_EntitySignatures[entity]);
		}

		// Pretty Expensive Operation so use this once, Cache the Pointer instead of
		// every Frame
		template <IsBaseOfComponent T> T* GetComponent(Entity entity)
		{
			T* _comp = dynamic_cast<T*>(
				m_ComponentArrays[typeid(T).name()]->m_EntityToComponent[entity]);

			return _comp;
		}

		// Checks if the given Entity has the Component of type T attached to it
		template <IsBaseOfComponent T> bool HasComponent(Entity entity)
		{
			// Check if there are any Components of that Type in the Scene
			if (!m_ComponentArrays[typeid(T).name()])
				return false;

			return m_ComponentArrays[typeid(T).name()]->m_EntityToComponent[entity] !=
				nullptr;
		}

		template <IsBaseOfSystem T>
		std::unique_ptr<System> CreateSystem(Signature signature)
		{
			std::unique_ptr<T> system =
				std::make_unique<T>(signature, m_Systems.size());
			m_Systems.insert(std::make_pair(system->m_Id, system));
		}

	public:
		// -- SYSTEMS
		Event<Entity, Signature> OnEntitySignatureChange;

		std::unique_ptr<StaticSpriteRenderer> m_StaticSpriteRenderer;

	private:
		// Holds Component Arrays by their typename
		std::map<const char*, BaseComponentArray*> m_ComponentArrays;
		std::map<u8, std::unique_ptr<System>> m_Systems;
		std::map<Entity, Signature> m_EntitySignatures;
		std::stack<Entity> m_EntityIdStack;

		u32 m_EntityCount = 0;

	private:
		void InitSystems();

		Entity GetNextEntityId();
	};
} // namespace tenshi
