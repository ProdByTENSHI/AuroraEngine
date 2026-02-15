#include "ecs/System.h"

#include "ecs/ComponentTypes.h"
#include "globals/EngineGlobals.hpp"
#include "tenshiUtil/container/STLUtil.h"

namespace Aurora
{
	System::System(Signature signature, u8 id)
		: m_Signature(signature), m_Id(id)
	{
		EventHandler<Entity, Signature> OnSignatureChange
		([this](Entity entity, Signature signature) {
			bool _isEntityPresent = STLUtil::IsElementInVector<Entity>(m_Entities, entity);
			if (m_Signature == signature) {
				if (!_isEntityPresent) {
					m_Entities.push_back(entity);
					return;
				}
			}
			else {
				if (!_isEntityPresent)
					return;

				// Remove Entity
				m_Entities.erase(STLUtil::GetItOfElementInVec(m_Entities, entity));
			}
			});
		g_Ecs->OnEntitySignatureChange += OnSignatureChange;
	}
}