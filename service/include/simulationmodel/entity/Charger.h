#ifndef Charger_H_
#define Charger_H_

#include "IEntity.h"

class Charger : public IEntity {
 public:
  /**
   * @brief Charger for the visual of a charger in the simulation
   * @param obj JSON object containing the charger's information
   */
  Charger(const JsonObject& obj);

  ~Charger();

  void update(double dt);
};

#endif
