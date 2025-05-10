#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <string>

/**
 * @brief This class sets up the observer pattern for notification
 */
class IObserver {
 public:
  /**
   * @brief notifies all observers
   *
   * @param message the Message to be notified to all in the observers vector
   */
  virtual void notify(const std::string &message) const = 0;
};

#endif  // IOBSERVER_H_
