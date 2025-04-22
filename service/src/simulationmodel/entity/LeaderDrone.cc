#include "LeaderDrone.h"
#include "BeelineStrategy.h"
#include <limits>

LeaderDrone::LeaderDrone(const JsonObject& obj) : Drone(obj), chargerPosition(-161, 226, 241) { 
    available = true;
    battery = 100.0; 
}

void LeaderDrone::update(double dt){

  battery -= ((this->getSpeed() > 0)? 0.01 : 0.005);




  if(waitingForHelper){
    return;
  }
  else if((battery - 20.0 < EPSILON) && lowBatNoti){
    lowBatNoti = false;

    HelperDrone* nearestHelper = findNearestHelper();
    if (nearestHelper) {
    std::string message = "LeaderDrone low battery - Help request sent to " + nearestHelper->getName();
    this->model->notify(message);
    if(package && pickedUp){
      //waitingForHelper = true;
    }

    //nearestHelper->assignHandoff(package);
    toCharger = new BeelineStrategy(getPosition(), chargerPosition);
    delete toFinalDestination;
    toFinalDestination = nullptr;
    delete toPackage;
    toPackage = nullptr;
    package = nullptr;
    return;

  } else {
    std::string message = "No available HelperDrone to handle handoff, recharging with package";
    this->model->notify(message);
  }

    //waitingForHelper = (this->);
    return;
  }






  if (available) getNextDelivery();

  if(toCharger){
    toCharger->move(this, dt);

    if (toCharger->isCompleted()) {
      std::string message = "LeaderDrone recharged to 100%";
      notifyObservers(message);
      delete toCharger;
      toCharger = nullptr;
      available = true;
      pickedUp = false;
      battery = 100.0;
      lowBatNoti = true;
    }
  }
  else if (toPackage) {
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

void LeaderDrone::recharge(){
    if(this->getPosition().dist(chargerPosition) < 5){
      battery = 100.0;
      lowBatNoti = true;
    }
}

HelperDrone * LeaderDrone::findNearestHelper(){
  HelperDrone * curr = nullptr;
  double distance = std::numeric_limits<double>::infinity();
  double currDist = 0.0;
    for(auto& helper : helpers){
      HelperDrone *origin = dynamic_cast<HelperDrone*>(helper->getOriginal());
      currDist = this->getPosition().dist(origin->getPosition());
      if(currDist < distance && origin->available){
        distance = currDist;
        curr = origin;
      }
    }
  return curr;
}

void LeaderDrone::addHelper(DroneColorDecorator* helper) { helpers.push_back(helper); }