#include "ChargerFactory.h"

IEntity* ChargerFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("Charger") == 0) {
    return new Charger(entity);
  }
  return nullptr;
}
