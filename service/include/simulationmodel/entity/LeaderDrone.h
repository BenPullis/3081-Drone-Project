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

/**
 * @class LeaderDrone
 * @brief Represents a LeaderDrone whos job is to complete deliveries.
 */
class LeaderDrone : public Drone {
 public:
  /**
   * @brief LeaderDrones are created with a name
   * @param obj JSON object containing the drone's information
   */
  LeaderDrone(const JsonObject& obj);

  /**
   * @brief Updates the LeaderDrone's position
   * @param dt Delta time
   */
  void update(double dt) override;

  /**
   * @brief Adds a HelperDrone to the leaders list of helpers
   * @param DroneColorDecorator* helper which is the wrapped HelperDrone
   */
  void addHelper(DroneColorDecorator* helper);

  /**
   * @brief sets the helpers to a vector of HelperDrones
   * @param std::vector<DroneColorDecorator*> drones which is all current helpers at the time of creation
   */
  void addAllHelpers(std::vector<DroneColorDecorator*> drones);

  /**
   * @brief Allows the LeaderDrones waitingforhelper bool to be changed
   * @param bool set which is the new bool value
   */
  void setWaiting(bool set);

 private:
  HelperDrone* findNearestHelper();

  double battery;

  std::vector<DroneColorDecorator*> helpers;

  bool lowBatNoti = true;

  bool waitingForHelper = false;

  Vector3 chargerPosition;

  IStrategy* toCharger = nullptr;

  std::string message;
};

#endif