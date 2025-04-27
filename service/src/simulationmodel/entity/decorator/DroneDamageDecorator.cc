#include "DroneDamageDecorator.h"

DroneDamageDecorator::DroneDamageDecorator(Drone* d, double dur)
    : DroneDecorator(d), durability(dur) {}

double DroneDamageDecorator::getDurability() const {
    return durability;
}

void DroneDamageDecorator::setDurability(double dur) {
    durability = dur;
}

void DroneDamageDecorator::update(double dt) {
    // this function and class as a whole really violates the single responsibility principle LOL
    // consider renaming this class, asking shonal/a TA if i can make the change that we don't touch
    // drone.cc
    SevereWeatherSystem* weather = SevereWeatherSystem::getInstance();
    windSpeed = weather->windSpeed;
    double magnitude = pow((pow(windSpeed[0], 2.0) + pow(windSpeed[2], 2.0)), 0.5);

    durability -= magnitude * 0.00001;

    // destroying the drone in the case of durability hitting 0
    // (IEntityDecorator already deletes sub in the case of the decorator being destroyed)
    if (durability <= 0.0){
        // delete this;
        std::cout << "death" << std::endl;
    } else {
        sub->update(dt);
        sub->setPosition(sub->getPosition() + Vector3(windSpeed) * sub->getSpeed() * 0.003 * dt);
    }
}
