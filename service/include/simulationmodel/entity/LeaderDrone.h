#ifndef LEADERDRONE_H_
#define LEADERDRONE_H_

#include "Drone.h"
#include "HelperDrone.h"
#include "IPublisher.h"
#include "Package.h"
#include <vector>

class LeaderDrone : public Drone {

    public:

        LeaderDrone(const JsonObject& obj);

        void update(double dt) override;

    private:
        void recharge();

        void requestHandoff();

        HelperDrone * findNearestHelper();

        double battery;
        std::vector<HelperDrone> helpers;

};

#endif