#ifndef HELPERDRONE_H_
#define HELPERDRONE_H_

#include "Drone.h"
#include "SimulationModel.h"
#include "IObserver.h"
#include "Package.h"

#include <vector>

class HelperDrone : public Drone, public IObserver {

    public:

        HelperDrone(const JsonObject& obj);

        void update(double dt) override;

        void notify(const std::string& message) const;

    private:

        void acceptHandoff(Package *package);
    
};

#endif