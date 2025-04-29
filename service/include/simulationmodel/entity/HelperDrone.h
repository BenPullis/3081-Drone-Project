#ifndef HELPERDRONE_H_
#define HELPERDRONE_H_

#include <vector>

#include "Drone.h"
#include "IObserver.h"
#include "LeaderDrone.h"
#include "Package.h"
#include "SimulationModel.h"

class LeaderDrone;

/**
 * @class HelperDrone
 * @brief Represents a HelperDrone whos job is to complete LeaderDrone
 * deliveries when requested.
 */
class HelperDrone : public Drone, public IObserver {
 public:
  /**
   * @brief HelperDrones are created with a name
   * @param obj JSON object containing the drone's information
   */
  HelperDrone(const JsonObject& obj);

  /**
   * @brief Updates the HelperDrone's position
   * @param dt Delta time
   */
  void update(double dt) override;

  /**
   * @brief Used to send notifications to the front end
   * @param String message to be displayed as a notification
   */
  void notify(const std::string& message) const;

  /**
   * @brief Called when the LeaderDrone needs to handoff a package to a
   * HelperDrone to complete the delivery
   * @param LeaderDrone* leader which is where the Helper needs to go to recieve
   * handoff
   * @param IStrategy* toFinalDestination which is the path to the final
   * destination that will be followed
   * @param Package* package which is the package to be grabbed at handoff
   */
  void assignHandoff(LeaderDrone* leader, IStrategy* toFinalDestination,
                     Package* package);

  /**
   * @brief Called when the LeaderDrone needs to complete the entire pickup and
   * delivery process
   * @param LeaderDrone* leader which is the helper's LeaderDrone
   * @param IStrategy* toPackage which is the path to the package that will be
   * followed
   * @param IStrategy* toFinalDestination which is the path to the final
   * destination that will be followed
   * @param Package* package which is the package to be grabbed at handoff
   */
  void assignDelivery(LeaderDrone* leader, IStrategy* toPackage,
                      IStrategy* toFinalDestination, Package* package);

 private:
  bool toLeader = false;

  LeaderDrone* leader = nullptr;

  std::string message;
};

#endif