#include <cstdlib>
#include <random>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>

// think about inheriting from ientity
class SevereWeatherSystem {
    private:
         static SevereWeatherSystem* instance;

        std::thread updateThread;
        std::atomic<bool> running;

        SevereWeatherSystem();

        void update();

        void stop();

        void updateLoop();

    public:
        SevereWeatherSystem(SevereWeatherSystem &other) = delete;

        void operator=(const SevereWeatherSystem &) = delete;

        static SevereWeatherSystem *getInstance();

        ~SevereWeatherSystem();

        std::vector<double> windSpeed = {0.0, 0.0, 0.0};
};