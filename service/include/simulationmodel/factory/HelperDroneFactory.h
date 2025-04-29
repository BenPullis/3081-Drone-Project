#ifndef HELPERDRONE_FACTORY_H_
#define HELPERDRONE_FACTORY_H_

#include <vector>

#include "Drone.h"
#include "DroneColorDecorator.h"
#include "HelperDrone.h"
#include "IEntityFactory.h"

/**
 *@brief HelperDrone Factory to produce HelperDrones class.
 **/
class HelperDroneFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for HelperDroneFactory class.
   **/
  virtual ~HelperDroneFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);
};

#endif