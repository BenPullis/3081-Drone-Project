#ifndef HUMAN_H_
#define HUMAN_H_

#include <string>
#include <vector>

#include "Disease.h"
#include "IEntity.h"
#include "IObserverDisease.h"
#include "IPublisherDisease.h"
#include "IReactionStrategy.h"
#include "IStrategy.h"

class IReactionStrategy;

/**
 * @class Human
 * @brief A human entity that can move, carry, receive, and spread diseases.
 */
class Human : public IEntity,
              public IPublisherDisease,
              public IObserverDisease {
 public:
  /**
   * @brief Constructs a Human from JSON data.
   * @param obj The configuration object.
   */
  Human(const JsonObject& obj);

  /**
   * @brief Destructor.
   */
  ~Human();

  /**
   * @brief Updates the human’s movement and disease progression.
   * @param dt Time delta.
   */
  void update(double dt);

  /**
   * @brief Publishes a random disease.
   */
  void publishDisease() override;

  /**
   * @brief Subscribes another human to this human's disease broadcasts.
   * @param human Pointer to the subscriber.
   */
  void subscribe(Human* human) override;

  /**
   * @brief Unsubscribes a human.
   * @param human Pointer to the human to remove.
   */
  void unsubscribe(Human* human) override;

  /**
   * @brief Called when this human receives a disease from another.
   * @param disease The disease transmitted.
   */
  void onDiseaseReceived(const Disease& disease) override;

 private:
  static Vector3 kellerPosition;

  IStrategy* movement = nullptr;
  bool atKeller = false;

  std::vector<Disease> knownDiseases;
  IReactionStrategy* reactionStrategy = nullptr;
  float opacity = 1.0f;
  std::vector<Human*> subscribers;
  float spreadTimer = 0.0f;
  const float spreadInterval = 5.0f;

  /**
   * @brief Manages the observers and notifies them of disease changes.
   */
  void manageObservers();

  /**
   * @brief Removes diseases that have fully recovered.
   */
  void removeCuredDiseases();

  /**
   * @brief Checks severity and handles death if needed.
   */
  void checkForDeath();

  /**
   * @brief Removes the human from the simulation.
   */
  void kill();

  /**
   * @brief Handles the sneeze / spread action.
   * @param dt Time delta.
   */
  void buildSpread(double dt);
};

#endif
