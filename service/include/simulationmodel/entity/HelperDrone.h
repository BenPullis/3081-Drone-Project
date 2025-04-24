#ifndef HELPERDRONE_H_
#define HELPERDRONE_H_

#include <vector>

#include "Drone.h"
#include "IObserver.h"
#include "Package.h"
#include "SimulationModel.h"
#include "LeaderDrone.h"

class LeaderDrone;

class HelperDrone : public Drone, public IObserver {
 public:
  HelperDrone(const JsonObject& obj);

  void update(double dt) override;

  void notify(const std::string& message) const;

  void assignHandoff(LeaderDrone* leader, IStrategy* toFinalDestination, Package* package);

  void assignDelivery(LeaderDrone* leader, IStrategy* toPackage, IStrategy* toFinalDestination, Package* package );

 private:
  bool toLeader = false;

  LeaderDrone *leader = nullptr;

  std::string message;
};

#endif