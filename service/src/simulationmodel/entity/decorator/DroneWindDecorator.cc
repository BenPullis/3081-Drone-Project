#include "DroneWindDecorator.h"

DroneWindDecorator::DroneWindDecorator(Drone* d, double dur, double spd)
    : DroneDecorator(d), durability(dur), speed(spd) {}

double DroneWindDecorator::getDurability() const { return durability; }

void DroneWindDecorator::setDurability(double dur) { durability = dur; }

void DroneWindDecorator::handleDeath() {
  hasDiedYet = true;
  sub->available = false;
  std::string message =
      sub->getName() + "'s durability fell to 0 and is no longer functional. ";
  sub->notifyObservers(message);
}

void DroneWindDecorator::update(double dt) {
  SevereWeatherSystem* weather = SevereWeatherSystem::getInstance();
  windSpeed = weather->windSpeed;
  double magnitude =
      pow((pow(windSpeed[0], 2.0) + pow(windSpeed[2], 2.0)), 0.5);

  durability -= magnitude * 0.0001;
  speed -= magnitude * 0.0001;

  if (durability <= 0.0 && hasDiedYet == false) {
    handleDeath();
  } else if (hasDiedYet == false) {
    sub->update(dt * (speed / 100.0));
    Vector3 newPos = (sub->getPosition() + Vector3(windSpeed) * 0.05 * dt);
    sub->setPosition(newPos);
  }
}

Drone* DroneWindDecorator::getOriginal() { return sub; }