#include "HelperDrone.h"

#include "BeelineStrategy.h"

HelperDrone::HelperDrone(const JsonObject& obj) : Drone(obj) {
  available = true;
}

void HelperDrone::update(double dt) {
  if (toLeader) {
    if (!toPackage) {
      toPackage =
          new BeelineStrategy(this->getPosition(), leader->getPosition());
    }

    toPackage->move(this, dt);

    if (toPackage->isCompleted()) {
      message = getName() + " picked up package from LeaderDrone";
      notifyObservers(message);

      delete toPackage;
      toPackage = nullptr;

      toLeader = false;
      pickedUp = true;
      available = false;

      leader->setWaiting(false);
    }
  } else if (toPackage) {
    toPackage->move(this, dt);

    if (toPackage->isCompleted()) {
      message = getName() + " picked up: " + package->getName();
      notifyObservers(message);
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      message = getName() + " dropped off: " + package->getName();
      notifyObservers(message);
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}

void HelperDrone::assignHandoff(LeaderDrone* leader,
                                IStrategy* toFinalDestination,
                                Package* package) {
  this->leader = leader;
  this->toFinalDestination = toFinalDestination;
  this->package = package;

  toLeader = true;
  available = false;
  pickedUp = false;
}

void HelperDrone::assignDelivery(LeaderDrone* leader, IStrategy* toPackage,
                                 IStrategy* toFinalDestination,
                                 Package* package) {
  this->leader = leader;
  this->toPackage = toPackage;
  this->toFinalDestination = toFinalDestination;
  this->package = package;

  available = false;
  pickedUp = false;
}

void HelperDrone::notify(const std::string& message) const {
  this->model->notify(message);
}