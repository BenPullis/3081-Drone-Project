// cppreference article for normal distribution:
// https://en.cppreference.com/w/cpp/numeric/random/normal_distribution

#include "SevereWeatherSystem.h"

SevereWeatherSystem::SevereWeatherSystem() : running(true) {
  updateThread = std::thread(&SevereWeatherSystem::updateLoop, this);
}

void SevereWeatherSystem::update() {
  double sigma = 20.0;
  // std::vector<double> deltaWind;

  // referred to cppreference when making normal distribution, see line 1
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> d(0.0, sigma);

  // populates windSpeed[0] and windSpeed[2] (horizontal)
  for (int i = 0; i < 3; i += 2) {
    double sample = d(gen);
    windSpeed[i] = windSpeed[i] * 0.8 + sample;
  }

  // ensuring the magnitude does not go over 200
  double magnitudeHorizontal =
      pow((pow(windSpeed[0], 2.0) + pow(windSpeed[2], 2.0)), 0.5);

  if (magnitudeHorizontal > 200.0) {
    windSpeed[0] = (windSpeed[0] / magnitudeHorizontal) * 200.0;
    windSpeed[2] = (windSpeed[2] / magnitudeHorizontal) * 200.0;
  }
}

SevereWeatherSystem* SevereWeatherSystem::getInstance() {
  if (instance == nullptr) {
    instance = new SevereWeatherSystem();
  }

  return instance;
}

// for the next two functions, c++ helped me use chrono/thread since i have
// limited familiarity

void SevereWeatherSystem::updateLoop() {
  while (running) {
    update();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void SevereWeatherSystem::stop() {
  running = false;
  if (updateThread.joinable()) {
    updateThread.join();
  }
}

SevereWeatherSystem::~SevereWeatherSystem() { stop(); }

SevereWeatherSystem* SevereWeatherSystem::instance = nullptr;