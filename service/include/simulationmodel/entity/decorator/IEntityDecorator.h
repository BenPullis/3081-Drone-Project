#ifndef ENTITY_DECORATOR_H_
#define ENTITY_DECORATOR_H_

#include <concepts>

#include "IEntity.h"

// Documentation pulled from our lab09 work.

template <std::derived_from<IEntity> T = IEntity>

/**
 * @brief A decorator interface for the IEntity class that forwards all methods to the underlying IEntity object.
 */
class IEntityDecorator : public T {
 public:
  IEntityDecorator(T* e) : T(e->getDetails()), sub(e) {}
  virtual ~IEntityDecorator() {
    if (sub) delete sub;
  }

  /**
   * @brief Links this entity to a simulation model,
   *  giving it access to the model's public variables
   *  and functions.
   * @param[in] model The simulation model to link.
   */
  virtual void linkModel(SimulationModel* model) {
    this->model = model;
    return sub->linkModel(model);
  }

  /**
   * @brief Gets the ID of the entity.
   * @return The ID of the entity.
   */
  virtual int getId() const { return sub->getId(); }

  /**
   * @brief Gets the position of the entity.
   * @return The position of the entity.
   */
  virtual Vector3 getPosition() const { return sub->getPosition(); }

  /**
   * @brief Gets the direction of the entity.
   * @return The direction of the entity.
   */
  virtual Vector3 getDirection() const { return sub->getDirection(); }

  /**
   * @brief Gets the details of the entity.
   * @return The details of the entity.
   */
  virtual const JsonObject& getDetails() const { return sub->getDetails(); }

  /**
   * @brief Gets the color of the entity
   * @return The color of the entity
   */
  virtual std::string getColor() const { return sub->getColor(); }

  /**
   * @brief Gets the name of the entity
   * @return The name of the entity
   */
  virtual std::string getName() const { return sub->getName(); }

  /**
   * @brief Gets the speed of the entity.
   * @return The speed of the entity.
   */
  virtual double getSpeed() const { return sub->getSpeed(); }

  /**
   * @brief Sets the position of the entity.
   * @param pos_ The desired position of the entity.
   */
  virtual void setPosition(Vector3 pos_) { return sub->setPosition(pos_); }

  /**
   *@brief Set the direction of the entity.
   *@param dir_ The new direction of the entity.
   */
  virtual void setDirection(Vector3 dir_) { return sub->setDirection(dir_); }

  /**
   * @brief Sets the color of the entity
   * @param col_ The new color of the entity
   */
  virtual void setColor(std::string col_) { return sub->setColor(col_); }

  /**
   * @brief Rotate the entity around y axis.
   * @param angle The angle to rotate the entity by.
   */
  virtual void rotate(double angle) { return sub->rotate(angle); }

  /**
   * @brief Updates the entity's position in the physical system.
   * @param dt The time step of the update.
   */
  virtual void update(double dt) { return sub->update(dt); }

  /**
   * @brief Adds an observer, used for notification system
   * @param o Const pointer to the observer.
   */
  virtual void addObserver(const IObserver* o) { return sub->addObserver(o); };

  /**
   * @brief Removes an observer, used for notification system
   * @param o Const pointer to the observer.
   */
  virtual void removeObserver(const IObserver* o) {
    return sub->removeObserver(o);
  };

  /**
   * @brief Notifies all observers with a given message
   * @param message String containing the message to be sent out
   */
  virtual void notifyObservers(const std::string& message) {
    return sub->notifyObservers(message);
  };

 protected:
  T* sub = nullptr;
};

#endif
