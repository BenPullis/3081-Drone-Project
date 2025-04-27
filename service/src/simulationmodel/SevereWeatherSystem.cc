// cppreference article for normal distribution: https://en.cppreference.com/w/cpp/numeric/random/normal_distribution

#include "SevereWeatherSystem.h"

SevereWeatherSystem::SevereWeatherSystem() : running(true) {
    updateThread = std::thread(&SevereWeatherSystem::updateLoop, this);
}

void SevereWeatherSystem::update() {

    double sigma = 50.0;
    // std::vector<double> deltaWind;

    // referred to cppreference when making normal distribution, see line 1
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0.0, sigma);

    // populates windSpeed[0] and windSpeed[2] (horizontal)
    for (int i = 0; i < 3; i += 2){
        double sample = d(gen);
        windSpeed[i] += sample;
    }

    // ensuring the magnitude does not go over 200
    double magnitudeHorizontal = pow((pow(windSpeed[0], 2.0) + pow(windSpeed[2], 2.0)), 0.5);

    if (magnitudeHorizontal > 200.0) {
        windSpeed[0] = (windSpeed[0] / magnitudeHorizontal) * 200.0;
        windSpeed[2] = (windSpeed[2] / magnitudeHorizontal) * 200.0;
    } else if (magnitudeHorizontal < -200) {
        // note to double check if the ones below should be multiplied by 200 or -200
        windSpeed[0] = (windSpeed[0] / magnitudeHorizontal) * 200.0;
        windSpeed[2] = (windSpeed[2] / magnitudeHorizontal) * 200.0;
    }

    std::cout << windSpeed[0] << ", " << windSpeed[2] << std::endl;
}

SevereWeatherSystem* SevereWeatherSystem::getInstance() {
    if (instance == nullptr){
        instance = new SevereWeatherSystem();
    }

    return instance;
}

void SevereWeatherSystem::updateLoop() {
    while (running) {
        update();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void SevereWeatherSystem::stop(){
    running = false;
    if (updateThread.joinable()) {
        updateThread.join();
    }
}

SevereWeatherSystem::~SevereWeatherSystem() {
    stop();
}

SevereWeatherSystem* SevereWeatherSystem::instance = nullptr;

// TODO: figure out how we're going to get all of the drones inside of the drones vector

// TODO: write documentation and make lint