#include "ecs/System.h"

#include "ecs/ComponentTypes.h"

namespace Aurora
{
	System::System(Signature signature, u8 id)
		: m_Signature(signature), m_Id(id)
	{
	}
}