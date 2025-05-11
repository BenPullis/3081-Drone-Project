#ifndef DRONE_COLOR_DECORATOR_H
#define DRONE_COLOR_DECORATOR_H

#include "Drone.h"
#include "DroneDecorator.h"
#include "Package.h"

// Documentation pulled from our lab09.

/**
 * @brief A decorator for Drone that dynamically changes its color during the
 * delivery process. The color is updated based on the drone's progress towards
 * the package and the destination.
 */
class DroneColorDecorator : public DroneDecorator {
 private:
  double hue = 0;
  double saturation = 0;
  double light = 0;
  double distToPackage = -1;
  double distToDestination = -1;

 public:
  /**
   * @brief Constructs a DroneColorDecorator wrapping a given Drone instance.
   * @param drone A pointer to the Drone instance to be decorated.
   * @param h Hue
   * @param s Saturation
   * @param l Lightness
   */
  DroneColorDecorator(Drone *d, double = 0, double = 0, double = 0);

  /**
   * @brief Gets the current color of the drone as an HSL string.
   * @return The drone's color as an HSL formatted string.
   */
  std::string getColor() const;

  /**
   * @brief Sets the color by adjusting the hue, saturation, and lightness.
   * @param h Hue
   * @param s Saturation
   * @param l Lightness
   */
  void setColor(double h, double s, double l);

  /**
   * @brief Updates the drone's state and color based on its progress.
   * @param dt Time delta for updating.
   */
  void update(double dt);

  /**
   * @brief Fetches the wrappee
   */
  Drone *getOriginal();
};

#endif  // DRONE_COLOR_DECORATOR_H
