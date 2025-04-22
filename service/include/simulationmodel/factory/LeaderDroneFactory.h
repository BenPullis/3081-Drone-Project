#ifndef LEADERDRONE_FACTORY_H_
#define LEADERDRONE_FACTORY_H_

#include <vector>

#include "Drone.h"
#include "DroneColorDecorator.h"
#include "IEntityFactory.h"
#include "LeaderDrone.h"

/**
 *@brief LeaderDrone Factory to produce LeaderDrones class.
 **/
class LeaderDroneFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for LeaderDroneFactory class.
   **/
  virtual ~LeaderDroneFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);
};

#endif