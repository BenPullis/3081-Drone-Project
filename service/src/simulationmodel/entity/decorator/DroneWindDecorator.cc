#include "DroneWindDecorator.h"

DroneWindDecorator::DroneWindDecorator(Drone* d, double dur)
    : DroneDecorator(d), durability(dur) {}

double DroneWindDecorator::getDurability() const { return durability; }

void DroneWindDecorator::setDurability(double dur) { durability = dur; }

void DroneWindDecorator::handleDeath() {
  hasDiedYet = true;
  std::string message =
      sub->getName() + "'s durability fell to 0 and is no longer functional. ";
  sub->notifyObservers(message);
}

void DroneWindDecorator::update(double dt) {
  SevereWeatherSystem* weather = SevereWeatherSystem::getInstance();
  std::vector<double> wind = (weather) ? weather->windSpeed : std::vector<double>{0.0, 0.0, 0.0};
  windSpeed = wind;
  double magnitude =
      pow((pow(windSpeed[0], 2.0) + pow(windSpeed[2], 2.0)), 0.5);

  durability -= magnitude * 0.0001;

  if (durability <= 0.0 && !hasDiedYet) {
    handleDeath();
    return;
  }
  sub->update(dt);
  Vector3 newPos = (sub->getPosition() + Vector3(windSpeed) * 0.05 * dt);
  sub->setPosition(newPos);
}

Drone* DroneWindDecorator::getOriginal() { return sub; }