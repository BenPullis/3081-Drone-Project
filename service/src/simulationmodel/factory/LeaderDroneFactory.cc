#include "LeaderDroneFactory.h"

IEntity* LeaderDroneFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("LeaderDrone") == 0) {
    std::cout << "LeaderDrone Created" << std::endl;
    return new DroneWindDecorator(
        new DroneColorDecorator(new LeaderDrone(entity), 0, 0, 100), 100, 100);
  }
  return nullptr;
}