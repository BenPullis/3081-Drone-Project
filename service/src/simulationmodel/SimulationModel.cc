#include "SimulationModel.h"


#include "ChargerFactory.h"
#include "HelicopterFactory.h"
#include "HelperDroneFactory.h"
#include "Disease.h"
#include "Human.h"
#include "HumanFactory.h"
#include "LeaderDroneFactory.h"
#include "PackageFactory.h"
#include "RobotFactory.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  entityFactory.addFactory(new LeaderDroneFactory());
  entityFactory.addFactory(new HelperDroneFactory());
  entityFactory.addFactory(new PackageFactory());
  entityFactory.addFactory(new RobotFactory());
  entityFactory.addFactory(new HumanFactory());
  entityFactory.addFactory(new HelicopterFactory());
  entityFactory.addFactory(new ChargerFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (auto& [id, entity] : entities) {
    delete entity;
  }
  delete graph;
}

IEntity* SimulationModel::createEntity(const JsonObject& entity) {
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = nullptr;
  if (myNewEntity = entityFactory.createEntity(entity)) {
    // Call AddEntity to add it to the view
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;
    // Add the simulation model as a observer to myNewEntity
    myNewEntity->addObserver(this);
  }

  // Used ChatGPT to figure out string comparison for both of these ifs
  if (entity["type"].toString() == "\"LeaderDrone\"") {
    if (myNewEntity) {
      std::cout << "yo1" << std::endl;
      DroneColorDecorator* curr = dynamic_cast<DroneColorDecorator*>(myNewEntity);
      std::cout << "yo2" << std::endl;
      // leaders.push_back(curr);
      std::cout << "yo3" << std::endl;
      std::cerr << "[DEBUG] myNewEntity actual type: "
                << typeid(*myNewEntity).name() << std::endl;
    } else {
      std::cerr << "[DEBUG] myNewEntity is null!" << std::endl;
    }

  }

  // Used ChatGPT to figure dynamic cast solution to a type issue
  if (entity["type"].toString() == "\"HelperDrone\"") {
    DroneColorDecorator* helper = dynamic_cast<DroneColorDecorator*>(myNewEntity);
    if (!helper) {
        std::cerr << "[ERROR] dynamic_cast to DroneColorDecorator failed!" << std::endl;
    } else if (leaders.empty()) {
        std::cerr << "[ERROR] Tried to add helper, but leaders list is empty!" << std::endl;
    } else {
      // for (auto& leader : leaders) {
      //   leader->addHelper(helper);
      // }
    }
  }

  return myNewEntity;
}

void SimulationModel::removeEntity(int id) { removed.insert(id); }

/// Schedules a Delivery for an object in the scene
void SimulationModel::scheduleTrip(const JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  Robot* receiver = nullptr;

  for (auto& [id, entity] : entities) {
    if (name == entity->getName()) {
      if (Robot* r = dynamic_cast<Robot*>(entity)) {
        if (r->requestedDelivery) {
          receiver = r;
          break;
        }
      }
    }
  }

  Package* package = nullptr;

  for (auto& [id, entity] : entities) {
    if (name + "_package" == entity->getName()) {
      if (Package* p = dynamic_cast<Package*>(entity)) {
        if (p->requiresDelivery()) {
          package = p;
          break;
        }
      }
    }
  }

  if (receiver && package) {
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    scheduledDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
  }
}

const routing::Graph* SimulationModel::getGraph() const { return graph; }

void SimulationModel::setGraph(const routing::Graph* graph) {
  if (this->graph) delete this->graph;
  this->graph = graph;
}

/// Updates the simulation
void SimulationModel::update(double dt) {
  for (auto& [id, entity] : entities) {
    entity->update(dt);
    controller.updateEntity(*entity);
  }
  for (int id : removed) {
    removeFromSim(id);
  }
  removed.clear();
}

void SimulationModel::stop(void) {}

void SimulationModel::removeFromSim(int id) {
  IEntity* entity = entities[id];
  if (entity) {
    for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end();
         ++i) {
      if (*i == entity) {
        scheduledDeliveries.erase(i);
        break;
      }
    }
    controller.removeEntity(*entity);
    entities.erase(id);
    delete entity;
  }
}

void SimulationModel::notify(const std::string& message) const {
  JsonObject details;
  details["message"] = message;
  this->controller.sendEventToView("Notification", details);
}

std::vector<IEntity*> SimulationModel::getEntities() const {
  std::vector<IEntity*> entityList;
  // copilot suggested this, this is exactly what I was going to do though
  for (const auto& pair : entities) {
    entityList.push_back(pair.second);
  }
  return entityList;
}

void SimulationModel::injectDisease(const JsonObject& data) {
  // Chatgpt recommended I add this check. Prompt: what should I add to this
  // function and add error checking
  if (!data.contains("targetName") || !data.contains("disease")) {
    std::cerr << "[injectDisease] Missing targetName or disease field."
              << std::endl;
    return;
  }

  std::string targetName = data["targetName"];
  JsonObject d = data["disease"];

  std::string name = d["name"];
  float duration = static_cast<float>(d["duration"]);
  float recoveryRate = static_cast<float>(d["recoveryRate"]);
  float severity = static_cast<float>(d["severity"]);

  Disease newDisease(name, duration, recoveryRate, severity);

  for (IEntity* entity : getEntities()) {
    if (entity->getName() == targetName) {
      Human* human = dynamic_cast<Human*>(entity);
      if (human) {
        human->onDiseaseReceived(newDisease);
        std::cout << "[injectDisease] Injected " << name << " into "
                  << targetName << std::endl;
      } else {
        std::cerr << "[injectDisease] Entity named " << targetName
                  << " is not a Human." << std::endl;
      }
      return;
    }
  }

  std::cerr << "[injectDisease] No Human found with name: " << targetName
            << std::endl;
}