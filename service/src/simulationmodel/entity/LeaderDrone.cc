#include "LeaderDrone.h"

#include <limits>

#include "BeelineStrategy.h"

LeaderDrone::LeaderDrone(const JsonObject& obj)
    : Drone(obj), chargerPosition(-160, 226, 241) {
  available = true;
  battery = 100.0;
}

void LeaderDrone::update(double dt) {
  battery -= ((available) ? 0.0075 : 0.0125);

  if (waitingForHelper) {
    return;
  } else if ((battery - 20.0 < 0) && lowBatNoti) {
    lowBatNoti = false;

    if (available) {
      toCharger = new BeelineStrategy(getPosition(), chargerPosition);
      message = "LeaderDrone low battery - Heading to recharge";
      this->model->notify(message);
      return;
    } else {

      HelperDrone* nearestHelper = findNearestHelper();

      if (nearestHelper) {
        message = "LeaderDrone low battery - Help request sent to " +
                  nearestHelper->getName();
        this->model->notify(message);
        if (!pickedUp) {
          nearestHelper->assignDelivery(this, toPackage, toFinalDestination, package);
          package = nullptr;
        } else {
          waitingForHelper = true;
          nearestHelper->assignHandoff(this, toFinalDestination, package);
        }
        toPackage = nullptr;
        toFinalDestination = nullptr;


        toCharger = new BeelineStrategy(getPosition(), chargerPosition);
        return;

      } else {
        message =
            "No available HelperDrone to handle handoff, heading to recharge";
        this->model->notify(message);
        toCharger = new BeelineStrategy(getPosition(), chargerPosition);
      }
    }

    return;
  }

  if (available) getNextDelivery();

  if (toCharger) {
    toCharger->move(this, dt);
    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toCharger->isCompleted()) {
      std::string message = "LeaderDrone recharged to 100%";
      notifyObservers(message);
      delete toCharger;
      toCharger = nullptr;
      available = (package) ? false : true;
      battery = 100.0;
      lowBatNoti = true;
    }
  } else if (toPackage) {
    toPackage->move(this, dt);

    if (toPackage->isCompleted()) {
      std::string message = getName() + " picked up: " + package->getName();
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
      std::string message = getName() + " dropped off: " + package->getName();
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

HelperDrone* LeaderDrone::findNearestHelper() {
  HelperDrone* curr = nullptr;
  double distance = std::numeric_limits<double>::infinity();
  double currDist = 0.0;
  for (auto& helper : helpers) {
    HelperDrone* origin = dynamic_cast<HelperDrone*>(helper->getOriginal());
    currDist = this->getPosition().dist(origin->getPosition());
    if (currDist < distance && origin->available) {
      distance = currDist;
      curr = origin;
    }
  }
  return curr;
}

void LeaderDrone::addHelper(DroneColorDecorator* helper) {
  helpers.push_back(helper);
}

void LeaderDrone::setWaiting(bool set) {
  waitingForHelper = set;
  package = nullptr;
}