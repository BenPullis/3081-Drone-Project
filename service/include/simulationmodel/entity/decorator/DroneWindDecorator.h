#ifndef DRONE_WIND_DECORATOR_H
#define DRONE_WIND_DECORATOR_H

#include "Drone.h"
#include "DroneDecorator.h"
#include "SevereWeatherSystem.h"
#include "Package.h"
#include "SimulationModel.h"

// Manages the wind and durability of
// a wrapped Drone, adjusting the position of
// the Drone based on the SevereWeatherSystem randomly generated wind and doing
// damage based on the magnitude of that wind. Makes drones "dead" when
// durability hits 0.
/**
 * @class DroneWindDecorator
 * @brief Manages the wind and durability of a wrapped Drone, adjusting the
 * position of the Drone based on the SevereWeatherSystem randomly generated
 * wind and doing damage based on the magnitude of that wind. Makes drones
 * "dead" when durability hits 0.
 */
class DroneWindDecorator : public DroneDecorator {
 private:
  double durability = 100.0;

  double speed = 100.0;

  std::vector<double> windSpeed = {0.0, 0.0, 0.0};

  bool hasDiedYet = false;

 public:
  /**
   * @brief Constructor setting the wrappee, the durability, and the speed.
   * @param d Drone object that will be wrapped.
   * @param dur Durability of the drone.
   * @param spd Speed of the drone.
   */
  DroneWindDecorator(Drone *d, double dur = 100.0, double spd = 100.0);

  /**
   * @brief Returns durability.
   */
  double getDurability() const;

  /**
   * @brief Sets durability.
   * @param dur New durability.
   */
  void setDurability(double dur);

  /**
   * @brief Sets hasDiedYet to true and notifies the system of a death.
   */
  void handleDeath();

  /**
   * @brief Fetches the windSpeed from the SevereWeatherSystem, uses its
   * magnitude to deal damage and updates speed and position based on windSpeed.
   */
  void update(double dt);

  /**
   * @brief Fetches the wrappee
   */
  Drone *getOriginal();
};

#endif  // DRONE_WIND_DECORATOR_H