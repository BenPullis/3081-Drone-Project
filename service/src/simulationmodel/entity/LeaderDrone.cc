#include "LeaderDrone.h"

LeaderDrone::LeaderDrone(const JsonObject& obj) : Drone(obj) { 
    available = true;
    battery = 100.0; 
}

void LeaderDrone::update(double dt){
  if(this->getSpeed() > 0){
    battery -= 0.005;
  }
  else{
    battery -= 0.0025;
  }

  if((battery - 20.0 < EPSILON) && lowBatNoti){
    lowBatNoti = false;
    std::string message = "LeaderDrone 20% battery - Time to handoff and recharge";
    this->model->notify(message);
  }
  
  if (available) getNextDelivery();

  if (toPackage) {
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
    lowBatNoti = true;
}

void LeaderDrone::requestHandoff(){
    
}

HelperDrone * LeaderDrone::findNearestHelper(){
    return nullptr;
}

void LeaderDrone::addHelper(DroneColorDecorator* helper) { helpers.push_back(helper); }