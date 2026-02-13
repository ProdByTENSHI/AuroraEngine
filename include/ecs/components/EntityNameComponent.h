#pragma once

#include "ecs/Component.h"

#include <string>

namespace Aurora {
class EntityNameComponent : public virtual Component {
public:
  explicit EntityNameComponent(const std::string &name);

  Node &Serialize() override;
  void Deserialize(Node &data) override;
  ComponentType GetType() override;

public:
  std::string m_Name = "Unnamed Entity";
};
} // namespace tenshi
