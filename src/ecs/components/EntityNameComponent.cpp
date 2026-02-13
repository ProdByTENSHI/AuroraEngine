#include "ecs/components/EntityNameComponent.h"

namespace Aurora {

EntityNameComponent::EntityNameComponent(const std::string& name)
    : m_Name(name) {}

ComponentType EntityNameComponent::GetType() {
    return ComponentType::EntityNameType;
}

} // namespace Aurora
