#ifndef PACKAGE_DECORATOR_H_
#define PACKAGE_DECORATOR_H_

#include "Drone.h"
#include "IEntityDecorator.h"
#include "Robot.h"

class DroneDecorator : public IEntityDecorator<Drone> {
 public:
  DroneDecorator(Drone* d) : IEntityDecorator(d) {}
  virtual void getNextDelivery() { return sub->getNextDelivery(); };
  Package* getPackage() override { return sub->getPackage(); };
  void linkModel(SimulationModel* m) override {
    this->model = m;
    sub->linkModel(m);
  }
  virtual IEntity* getOriginal() { return sub; };
};

#endif