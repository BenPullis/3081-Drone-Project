#ifndef DRONE_DAMAGE_DECORATOR_H
#define DRONE_DAMAGE_DECORATOR_H


#include "Drone.h"
#include "SevereWeatherSystem.h"
#include "DroneDecorator.h"

class DroneDamageDecorator : public DroneDecorator {
 private:
  double durability = 100.0;
  std::vector<double> windSpeed;

 public:
  DroneDamageDecorator(Drone* d, double = 100.0);
  double getDurability() const;
  void setDurability(double dur);
  void update(double dt);
};

#endif  // DRONE_DAMAGE_DECORATOR_H