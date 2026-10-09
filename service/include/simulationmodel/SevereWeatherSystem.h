#include <atomic>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <thread>

// Singleton that generates wind on a horizontal plane used by all Drones in the
// simulation, based on a random number generator algorithm that runs every
// second.
/**
 * @class SevereWeatherSystem
 * @brief Singleton that generates wind on a horizontal plane used by all Drones
 * in the simulation, based on a random number generator algorithm that runs
 * every second.
 */
class SevereWeatherSystem {
 private:
  static SevereWeatherSystem *instance;

  std::thread updateThread;
  std::atomic<bool> running;

  /**
   * @brief Constructor, creates a new thread that will be used to run the
   * updateLoop.
   */
  SevereWeatherSystem();

  /**
   * @brief Performs horizontal plane random wind generation based off of
   * a normal distribution. Ensures the magnitude does not go over 200.
   */
  void update();

  /**
   * @brief Halts the updateLoop.
   */
  void stop();

  /**
   * @brief Calls update every one second.
   */
  void updateLoop();

 public:
  /**
   * @brief Overriding copy constructor to prevent creation of multiple
   * Singletons.
   */
  SevereWeatherSystem(SevereWeatherSystem &other) = delete;

  /**
   * @brief Overriding assignment constructor to prevent creation of multiple
   * Singletons.
   */
  void operator=(const SevereWeatherSystem &) = delete;

  /**
   * @brief Retrieves an instance of the Singleton.
   */
  static SevereWeatherSystem *getInstance();

  /**
   * @brief Destructor, calls stop method.
   */
  ~SevereWeatherSystem();

  std::vector<double> windSpeed = {0.0, 0.0, 0.0};
};