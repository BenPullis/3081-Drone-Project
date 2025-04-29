#include "HelperDroneFactory.h"

IEntity* HelperDroneFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("HelperDrone") == 0) {
    std::cout << "HelperDrone Created" << std::endl;
    return new DroneColorDecorator(new HelperDrone(entity), 0, 0, 100);
  }
  return nullptr;
}