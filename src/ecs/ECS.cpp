#include "ecs/Ecs.h"

#include "globals/EngineGlobals.hpp"
#include <cstdio>

namespace Aurora
{
	Ecs::Ecs() {}

	Ecs::~Ecs() {}

	Entity Ecs::CreateEntity()
	{
		Entity _entity = GetNextEntityId();
		++m_EntityCount;

		return _entity;
	}

	void Ecs::DestroyEntity(Entity entity)
	{
		for (auto& arr : m_ComponentArrays)
		{
			arr.second->OnEntityDestroyed(entity);
		}

		m_EntitySignatures[entity].reset();
		OnEntitySignatureChange.Dispatch(entity, m_EntitySignatures[entity]);

		m_EntityIdStack.push(entity);
		--m_EntityCount;
	}

	bool Ecs::IsEntityValid(Entity entity)
	{
		return m_EntitySignatures.find(entity) != m_EntitySignatures.end();
	}

	Entity Ecs::GetEntityOnPosition(const glm::vec2& screenSpacePos)
	{
		// TODO: Implement
		return INVALID_ENTITY;
	}

	void Ecs::InitSystems()
	{
	}

	u32 Ecs::GetNextEntityId()
	{
		u32 _id = 0;
		if (m_EntityIdStack.size() > 0)
		{
			_id = m_EntityIdStack.top();
			m_EntityIdStack.pop();
		}
		else
		{
			_id = m_EntityCount;
		}

		return _id;
	}

	void Ecs::Init() { InitSystems(); }

	// TODO: Handle Case where Entity IDs are higher than the Entity Count because
	// Entities before them got deleted
	void Ecs::DestroyAllEntities()
	{
		u32 _entityCount = m_EntityCount;
		for (u32 i = 0; i < _entityCount; i++)
		{
			DestroyEntity(i);
		}
	}
} // namespace Aurora