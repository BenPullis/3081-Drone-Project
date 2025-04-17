#include "Human.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "AcceptStrategy.h"
#include "AstarStrategy.h"
#include "IReactionStrategy.h"
#include "RejectStrategy.h"
#include "SimulationModel.h"
#include "VariantStrategy.h"

Vector3 Human::kellerPosition(64.0, 254.0, -210.0);

Human::Human(const JsonObject& obj) : IEntity(obj) {}

Human::~Human() {
  if (movement) delete movement;
  if (reactionStrategy) delete reactionStrategy;
}

void Human::update(double dt) {
  // Movement
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
    bool nearKeller = this->position.dist(Human::kellerPosition) < 85;
    if (nearKeller && !this->atKeller) {
      std::string message = this->getName() + " visited Keller hall";
      notifyObservers(message);
    }
    atKeller = nearKeller;
  } else {
    if (movement) delete movement;
    Vector3 dest;
    dest.x = ((double)rand() / RAND_MAX) * 2900 - 1400;
    dest.y = position.y;
    dest.z = ((double)rand() / RAND_MAX) * 1600 - 800;
    if (model) movement = new AstarStrategy(position, dest, model->getGraph());
  }

  // Disease ticking
  for (Disease& d : knownDiseases) {
    d.setDuration(d.getDuration() - d.getRecoveryRate() * dt);
    if (d.getDuration() < 0) d.setDuration(0);
  }

  removeCuredDiseases();
  checkForDeath();
  setColor();
  manageObservers();

  // Automatic disease spreading every 5 seconds
  spreadTimer += dt;
  if (spreadTimer >= spreadInterval) {
    publishDisease();
    // Optional: show disease spreading animation
    spreadTimer = 0.0f;
  }
}

void Human::setColor() {
  if (knownDiseases.empty()) {
    opacity = 1.0f;
  } else {
    // ChatGPT: Calculate opacity based on disease severity
    float avgRatio = 0.0f;
    for (const Disease& d : knownDiseases) {
      avgRatio += d.getDuration() / d.getRecoveryRate();
    }
    avgRatio /= knownDiseases.size();
    opacity = std::max(0.1f, std::min(1.0f, avgRatio / 10.0f));
    std::cout << getName() << " is infected with opacity: " << opacity
              << std::endl;
  }

  // todo: actually render the human with the opacity
}

void Human::publishDisease() {
  float sneezeSeverity = 1 + static_cast<float>(rand()) /
                                 (static_cast<float>(RAND_MAX / (1.0f - 0.1f)));

  // Chatgpt: refactor this to publish one random disease instead of first one

  std::vector<Disease> activeDiseases;
  for (const Disease& d : knownDiseases) {
    if (!d.isCured()) {
      activeDiseases.push_back(d);
    }
  }

  if (activeDiseases.empty()) return;

  // Choose one at random
  int randI = rand() % activeDiseases.size();
  Disease spread = activeDiseases[randI];
  spread.setSeverity(spread.getSeverity() * sneezeSeverity);

  for (Human* sub : subscribers) {
    sub->onDiseaseReceived(spread);
  }
}

void Human::subscribe(Human* human) {
  if (std::find(subscribers.begin(), subscribers.end(), human) ==
      subscribers.end()) {
    subscribers.push_back(human);
  }
}

void Human::unsubscribe(Human* human) {
  subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), human),
                    subscribers.end());
}

void Human::onDiseaseReceived(const Disease& disease) {
  int choice = rand() % 3;
  std::string choiceText;

  switch (choice) {
    case 0:
      reactionStrategy = new AcceptStrategy();
      choiceText = " Accepted ";
      break;
    case 1:
      reactionStrategy = new RejectStrategy();
      choiceText = " Rejected ";
      break;
    case 2:
      reactionStrategy = new VariantStrategy();
      choiceText = " Mutated ";
      break;
  }

  notifyObservers(getName() + choiceText + disease.getName());

  Disease result = reactionStrategy->processDisease(disease);
  if (!result.isCured()) {
    knownDiseases.push_back(result);
  }
}

void Human::removeCuredDiseases() {
  std::vector<Disease> stillSick;
  for (const Disease& d : knownDiseases) {
    if (d.isCured()) {
      notifyObservers(getName() + " conquered " + d.getName());
    } else {
      stillSick.push_back(d);
    }
  }
  knownDiseases = stillSick;
}

void Human::checkForDeath() {
  int totalSeverity = 0;
  for (const Disease& d : knownDiseases) {
    totalSeverity += d.getSeverity();
  }

  if (totalSeverity > 10) {
    std::string msg = getName() + " met their demise to [";
    for (size_t i = 0; i < knownDiseases.size(); ++i) {
      msg += knownDiseases[i].getName();
      if (i < knownDiseases.size() - 1) {
        msg += ", ";
      }
    }
    msg += "]";
    std::cout << msg << std::endl;
    notifyObservers(msg);
    // model->removeEntity(this->getId()); // this does NOT work sob
    // Optional: spawn gravestone
  }
}

void Human::manageObservers() {
  if (!model) return;

  float maxRadius = 10;
  if (maxRadius <= 0.0f) return;

  for (IEntity* entity : model->getEntities()) {
    Human* other = dynamic_cast<Human*>(entity);
    if (!other || other == this) continue;  // ignore this human and non-humans

    float dist = this->getPosition().dist(other->getPosition());

    if (dist <= maxRadius) {
      // Copilot: make the condition to subscribe more readable
      if (std::find(subscribers.begin(), subscribers.end(), other) ==
          subscribers.end()) {
        subscribe(other);
      }
    } else {
      if (std::find(subscribers.begin(), subscribers.end(), other) !=
          subscribers.end()) {
        unsubscribe(other);
      }
    }
  }
}
