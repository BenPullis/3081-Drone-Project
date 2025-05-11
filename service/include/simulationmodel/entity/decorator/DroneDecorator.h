#ifndef PACKAGE_DECORATOR_H_
#define PACKAGE_DECORATOR_H_

#include "Drone.h"
#include "IEntityDecorator.h"
#include "Robot.h"

// Documentation pulled from our lab09 work.

/**
 * @brief A decorator for the Drone class that forwards all methods to the underlying Drone object.
 */
class DroneDecorator : public IEntityDecorator<Drone> {
 public:
  /**
  * @brief Constructs a DroneDecorator wrapping a given Drone instance.
  * @param d A pointer to the Drone instance to be decorated.
  */
  DroneDecorator(Drone* d) : IEntityDecorator(d) {}

  /**
  * @brief Gets the next delivery for the drone.
  */
  virtual void getNextDelivery() { return sub->getNextDelivery(); };

  /**
  * @brief Gets the package currently being carried by the decorated Drone.
  * @return Pointer to the Package instance being carried.
  */
  Package* getPackage() override { return sub->getPackage(); };

  /**
  * @brief Links the decorated Drone to the simulation model.
  * @param m Pointer to the SimulationModel instance.
  */
  void linkModel(SimulationModel* m) override {
    this->model = m;
    sub->linkModel(m);
  }

  /**
  * @brief Fetches the wrappee
  */
  virtual IEntity* getOriginal() { return sub; };
};

#endif
