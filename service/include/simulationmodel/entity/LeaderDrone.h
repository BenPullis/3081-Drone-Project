#ifndef LEADERDRONE_H_
#define LEADERDRONE_H_

#include <cmath>
#include <vector>

#include "Drone.h"
#include "DroneColorDecorator.h"
#include "HelperDrone.h"
#include "IPublisher.h"
#include "Package.h"
#include "vector3.h"

class HelperDrone;

class LeaderDrone : public Drone {
 public:
  LeaderDrone(const JsonObject& obj);

  void update(double dt) override;

  void addHelper(DroneColorDecorator* helper);

 private:

  void requestHandoff();

  HelperDrone* findNearestHelper();

  double battery;

  std::vector<DroneColorDecorator*> helpers;

  const double EPSILON = 1e-6;

  bool lowBatNoti = true;

  bool waitingForHelper = false;

  bool recharging = false;

  Vector3 chargerPosition;

  IStrategy* toCharger = nullptr;

  std::string message;
};

#endif