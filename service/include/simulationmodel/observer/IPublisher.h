#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <set>
#include <string>

#include "IObserver.h"

/**
 * @brief This class adds, removes, and notifies as per the Observer design
 * pattern
 */
class IPublisher {
public:
  /**
   * @brief adds an Observer to the observers vector
   *
   * @param o the Observer to be added
   */
  virtual void addObserver(const IObserver *o);
  /**
   * @brief removes an Observer from the observers vector
   *
   * @param o the Observer to be removed
   */
  virtual void removeObserver(const IObserver *o);
  /**
   * @brief notifies all observers
   *
   * @param message the Message to be notified to all in the observers vector
   */
  virtual void notifyObservers(const std::string &message);

protected:
  std::set<const IObserver *> observers;
};

#endif // IPUBLISHER_H_
