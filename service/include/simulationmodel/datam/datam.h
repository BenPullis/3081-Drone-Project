#include "IEntity.h"
#include "math/vector3.h"
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <random>
#include <thread>

// Singleton that manages (exports) data from simulation to a CSV file
/**
 * @class SevereWeatherSystem
 * @brief Singleton that generates wind on a horizontal plane used by all Drones
 * in the simulation, based on a random number generator algorithm that runs
 * every second.
 */
class Datam {
private:
  static Datam *instance;

  std::thread updateThread;
  std::atomic<bool> running;

  /**
   * @brief Singleton constructor
   */
  Datam();

  /**
   * @brief updates the struct of data when called
   */
  void update();

  /**
   * @brief Halts the updateLoop.
   */
  void stop();

  /**
   * @brief Updates every 5 seconds
   * @param entity the entity to be updated
   */
  void updateLoop();

  struct entry {
    std::string name;
    Vector3 position;
    std::chrono::system_clock::time_point timestamp;
  };

  int toggledOn = 0;

public:
  /**
   * @brief Overriding copy constructor to prevent creation of multiple
   * Singletons.
   */
  Datam(Datam &other) = delete;

  /**
   * @brief Overriding assignment constructor to prevent creation of multiple
   * Singletons.
   */
  void operator=(const Datam &) = delete;

  /**
   * @brief Retrieves an instance of the Singleton.
   */
  static Datam *getInstance();

  /**
   * @brief Destructor, calls stop method.
   */
  ~Datam();

  int publicUpdate(IEntity *entity);
  // std::vector<double> windSpeed = {0.0, 0.0, 0.0};

  void toggleUpdate();

  std::map<IEntity *, entry> dataEntries;
};